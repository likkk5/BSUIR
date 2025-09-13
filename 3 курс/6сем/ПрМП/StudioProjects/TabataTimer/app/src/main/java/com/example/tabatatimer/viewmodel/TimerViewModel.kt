package com.example.tabatatimer.viewmodel

import android.app.Application
import android.content.*
import android.os.IBinder
import android.util.Log
import androidx.lifecycle.*
import com.example.tabatatimer.data.AppDatabase
import com.example.tabatatimer.data.TimerSequence
import com.example.tabatatimer.service.TimerService
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch

class TimerViewModel(application: Application) : AndroidViewModel(application) {

    private val dao = AppDatabase.getDatabase(application).timerDao()

    val sequences: LiveData<List<TimerSequence>> = dao.getAll()

    private val _currentTime = MutableLiveData<Pair<Long, Int>>() // (время, индекс фазы)
    val currentTime: LiveData<Pair<Long, Int>> get() = _currentTime

    private val _isDataInserted = MutableLiveData<Boolean>()
    val isDataInserted: LiveData<Boolean> get() = _isDataInserted

    private var serviceIntent: Intent? = null
    private var timerService: TimerService? = null
    private var isBound = false
    private var phaseDurations: List<Long> = listOf()
    private var totalElapsedTime = 0L

    fun startService(context: Context, sequence: TimerSequence) {
        if (serviceIntent == null) { // 🔹 Запускаем только если сервис еще не запущен
            phaseDurations = mutableListOf<Long>().apply {
                if (sequence.warmUp > 0) add(sequence.warmUp * 1000L)
                repeat(sequence.repetitions) {
                    add(sequence.workout * 1000L)
                    if (sequence.rest > 0) add(sequence.rest * 1000L)
                }
                if (sequence.cooldown > 0) add(sequence.cooldown * 1000L)
            }

            serviceIntent = Intent(context, TimerService::class.java).apply {
                putExtra("PHASES", phaseDurations.toLongArray())
            }
            context.startService(serviceIntent)
        }

        bindService(context)
    }


    fun bindService(context: Context) {
        serviceIntent?.let {
            context.bindService(it, serviceConnection, Context.BIND_AUTO_CREATE)
            Log.d("TimerViewModel", "Сервис привязан")
        }
    }

    private val serviceConnection = object : ServiceConnection {
        override fun onServiceConnected(name: ComponentName?, service: IBinder?) {
            val binder = service as TimerService.TimerBinder
            timerService = binder.getService()
            isBound = true

            timerService?.setTimerListener { timeLeft, phaseIndex ->
                Log.d("TimerViewModel", "Слушатель таймера: ${timeLeft} сек, Фаза: $phaseIndex")
                _currentTime.postValue(timeLeft to phaseIndex)
            }

        }

        override fun onServiceDisconnected(name: ComponentName?) {
            isBound = false
        }
    }

    fun pauseTimer() {
        if (!isBound || timerService == null) return
        timerService?.pauseTimer()
        timerService?.getRemainingTime()?.let { timeLeft ->
            _currentTime.postValue((timeLeft / 1000).coerceAtLeast(0) to calculatePhaseIndex(totalElapsedTime))
        }
    }

    fun resumeTimer() {
        if (!isBound || timerService == null) return
        timerService?.resumeTimer()
        timerService?.getRemainingTime()?.let { timeLeft ->
            _currentTime.postValue((timeLeft / 1000).coerceAtLeast(0) to calculatePhaseIndex(totalElapsedTime))
        }
    }

    fun stopService(context: Context) {
        if (!isBound) return
        context.unbindService(serviceConnection)
        isBound = false
        serviceIntent?.let { context.stopService(it) }
        _currentTime.postValue(0L to 0)
    }

    private fun calculatePhaseIndex(elapsedTime: Long): Int {
        var sum = 0L
        for (i in phaseDurations.indices) {
            sum += phaseDurations[i] / 1000
            if (elapsedTime < sum) return i
        }
        return phaseDurations.size - 1
    }

    fun addSequence(sequence: TimerSequence) {
        viewModelScope.launch(Dispatchers.IO) {
            dao.insert(sequence)
            Log.d("TimerViewModel", "Добавлен новый таймер: ${sequence.title}")
        }
    }

    fun deleteSequence(sequence: TimerSequence) {
        viewModelScope.launch(Dispatchers.IO) {
            dao.delete(sequence)
            Log.d("TimerViewModel", "Удалён таймер: ${sequence.title}")
        }
    }

    fun updateSequence(sequence: TimerSequence) {
        viewModelScope.launch(Dispatchers.IO) {
            dao.update(sequence)
            Log.d("TimerViewModel", "Обновлен таймер: ${sequence.title}")
        }
    }

    fun clearAllSequences() {
        viewModelScope.launch(Dispatchers.IO) {
            dao.deleteAll()
            Log.d("TimerViewModel", "Все таймеры удалены")
        }
    }

    fun loadSequences() {
        viewModelScope.launch(Dispatchers.Main) {
            sequences.value?.size?.let { count ->
                Log.d("TimerViewModel", "Загружено $count таймеров из БД")
            }
        }
    }

    fun getSequenceById(id: Int): LiveData<TimerSequence> {
        return dao.getSequenceById(id)
    }

    fun insertTestData() {
        viewModelScope.launch(Dispatchers.IO) {
            if (dao.getAll().value.isNullOrEmpty()) {
                dao.insert(
                    TimerSequence(
                        title = "Тест 1",
                        duration = 30,
                        warmUp = 10,
                        workout = 20,
                        rest = 10,
                        cooldown = 5,
                        repetitions = 3,
                        color = "#FF0000"
                    )
                )
                dao.insert(
                    TimerSequence(
                        title = "Тест 2",
                        duration = 60,
                        warmUp = 15,
                        workout = 30,
                        rest = 15,
                        cooldown = 10,
                        repetitions = 5,
                        color = "#00FF00"
                    )
                )
                Log.d("TimerViewModel", "Добавлены тестовые данные")
                _isDataInserted.postValue(true)
            } else {
                _isDataInserted.postValue(false)
            }
        }
    }
}
