package com.example.tabatatimer.ui.screens

import android.media.MediaPlayer
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.viewModels
import com.example.tabatatimer.R
import com.example.tabatatimer.viewmodel.TimerViewModel
import com.example.tabatatimer.databinding.FragmentTimerBinding

class TimerFragment : Fragment() {
    private lateinit var binding: FragmentTimerBinding
    private val viewModel: TimerViewModel by viewModels()
    private var sequenceId: Int = -1
    private var mediaPlayer: MediaPlayer? = null

    private var lastPhaseIndex: Int = -1 // Следим за сменой фаз

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View {
        binding = FragmentTimerBinding.inflate(inflater, container, false)

        sequenceId = arguments?.getInt("sequence_id") ?: -1
        if (sequenceId == -1) {
            Toast.makeText(requireContext(), "Ошибка: Неверный sequenceId", Toast.LENGTH_SHORT).show()
            return binding.root
        }

        viewModel.currentTime.observe(viewLifecycleOwner) { (time, phaseIndex) ->
            Log.d("TimerFragment", "Обновление UI: Фаза $phaseIndex, Время: $time сек")

            val phaseNames = listOf("Разминка", "Работа", "Отдых", "Заминка")
            val phase = phaseNames.getOrElse(phaseIndex % phaseNames.size) { "Фаза $phaseIndex" }

            if (phaseIndex != lastPhaseIndex) {
                lastPhaseIndex = phaseIndex
                playSound(R.raw.beep_sound) // Звук смены фазы
            }

            binding.timerText.text = "$time сек"
            binding.phaseText.text = "Фаза: $phase"
        }

        viewModel.getSequenceById(sequenceId).observe(viewLifecycleOwner) { sequence ->
            sequence?.let {
                Log.d("TimerFragment", "Получен таймер: ${it.title}, duration = ${it.duration}")

                binding.timerTitle.text = it.title
                val durationMs = it.duration * 1000
                val phaseTimes = mutableListOf<Long>().apply {
                    val warmUp = it.warmUp.toLong()
                    val workout = it.workout.toLong()
                    val rest = it.rest.toLong()
                    val cooldown = it.cooldown.toLong()
                    val repetitions = it.repetitions

                    if (warmUp > 0) add(warmUp) // Разминка один раз в начале

                    repeat(repetitions) {
                        add(workout)         // Работа
                        if (rest > 0) add(rest) // Отдых
                    }

                    if (cooldown > 0) add(cooldown) // Заминка один раз в конце
                }

                // Определяем первую фазу и её время
                val firstPhaseTime = phaseTimes.firstOrNull() ?: 0
                val firstPhaseName = when {
                    it.warmUp > 0 -> "Разминка"
                    it.repetitions > 0 -> "Работа"
                    it.cooldown > 0 -> "Заминка"
                    else -> "Неизвестная фаза"
                }

                binding.timerText.text = "$firstPhaseTime сек"
                binding.phaseText.text = "Фаза: $firstPhaseName"

                binding.startButton.setOnClickListener {
                    Log.d("TimerFragment", "Нажатие Start: durationMs = $durationMs")
                    viewModel.startService(requireContext(), sequence)
                }
            } ?: Log.e("TimerFragment", "Ошибка: sequence == null")
        }

        binding.stopButton.setOnClickListener {
            stopSound()
            viewModel.stopService(requireContext())
        }
        binding.pauseButton.setOnClickListener {
            stopSound()
            viewModel.pauseTimer()
        }
        binding.resumeButton.setOnClickListener {
            viewModel.resumeTimer()
        }

        return binding.root
    }


    private fun playSound(soundResId: Int) {
        if (mediaPlayer?.isPlaying == true) return

        mediaPlayer = MediaPlayer.create(requireContext(), soundResId)
        mediaPlayer?.start()

        mediaPlayer?.setOnCompletionListener {
            it.release()
            mediaPlayer = null
        }
    }

    private fun stopSound() {
        mediaPlayer?.let {
            if (it.isPlaying) {
                it.stop()
                it.release()
            }
            mediaPlayer = null
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        stopSound()
    }
}
