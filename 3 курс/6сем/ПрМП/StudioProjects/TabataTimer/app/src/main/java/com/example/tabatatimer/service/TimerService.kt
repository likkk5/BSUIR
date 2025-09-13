package com.example.tabatatimer.service

import android.app.*
import android.content.Intent
import android.os.*
import android.util.Log
import androidx.core.app.NotificationCompat
import com.example.tabatatimer.R

class TimerService : Service() {
    private val binder = TimerBinder()
    private var countDownTimer: CountDownTimer? = null
    private var remainingTime: Long = 0
    private var isRunning = false
    private var timerListener: ((Long, Int) -> Unit)? = null
    private var phaseDurations: List<Long> = listOf()
    private var currentPhaseIndex = 0

    override fun onCreate() {
        super.onCreate()
        startForeground(NOTIFICATION_ID, createNotification("Таймер готов"))
        Log.d("TimerService", "Сервис создан")
    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        phaseDurations = intent?.getLongArrayExtra("PHASES")?.toList() ?: listOf()
        if (phaseDurations.isEmpty()) {
            stopSelf()
            return START_NOT_STICKY
        }
        currentPhaseIndex = 0
        startNextPhase()
        return START_STICKY
    }

    override fun onBind(intent: Intent?): IBinder = binder

    private fun startNextPhase(startTime: Long? = null) {
        if (currentPhaseIndex >= phaseDurations.size) {
            stopSelf()
            return
        }

        val duration = startTime ?: phaseDurations[currentPhaseIndex]
        remainingTime = duration
        isRunning = true

        countDownTimer?.cancel()
        countDownTimer = object : CountDownTimer(duration, 1000) {
            override fun onTick(millisUntilFinished: Long) {
                remainingTime = millisUntilFinished
                val secondsLeft = (millisUntilFinished / 1000) + 1
                Log.d("TimerService", "Tick: $secondsLeft сек, Фаза: $currentPhaseIndex")
                timerListener?.invoke(secondsLeft, currentPhaseIndex)
            }

            override fun onFinish() {
                timerListener?.invoke(0, currentPhaseIndex) // ✅ Теперь передает 0 перед переходом
                currentPhaseIndex++
                Handler(Looper.getMainLooper()).postDelayed({ startNextPhase() }, 500) // ✅ Добавлена пауза перед сменой фазы
            }
        }.start()
    }

    fun pauseTimer() {
        if (!isRunning) return
        countDownTimer?.cancel()
        isRunning = false
    }

    fun resumeTimer() {
        if (isRunning) return
        startNextPhase(remainingTime)
    }

    fun getRemainingTime(): Long = remainingTime

    fun setTimerListener(listener: (Long, Int) -> Unit) {
        timerListener = listener
    }

    override fun onDestroy() {
        countDownTimer?.cancel()
        super.onDestroy()
    }

    private fun createNotification(text: String): Notification {
        val channelId = "timer_channel"
        val notificationManager = getSystemService(NotificationManager::class.java)

        if (notificationManager.getNotificationChannel(channelId) == null) {
            val channel = NotificationChannel(channelId, "Таймер", NotificationManager.IMPORTANCE_LOW)
            notificationManager.createNotificationChannel(channel)
        }

        return NotificationCompat.Builder(this, channelId)
            .setContentTitle("Tabata Таймер")
            .setContentText(text)
            .setSmallIcon(R.drawable.ic_timer)
            .setOngoing(true)
            .build()
    }

    inner class TimerBinder : Binder() {
        fun getService(): TimerService = this@TimerService
    }

    companion object {
        private const val NOTIFICATION_ID = 1
    }
}
