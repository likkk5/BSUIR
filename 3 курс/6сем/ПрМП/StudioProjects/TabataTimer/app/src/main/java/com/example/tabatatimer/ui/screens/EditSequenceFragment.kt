package com.example.tabatatimer.ui.screens

import android.content.Context
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.view.inputmethod.InputMethodManager
import androidx.fragment.app.Fragment
import androidx.fragment.app.viewModels
import androidx.navigation.fragment.findNavController
import com.example.tabatatimer.databinding.FragmentEditSequenceBinding
import com.example.tabatatimer.data.TimerSequence
import com.example.tabatatimer.viewmodel.TimerViewModel
import com.google.android.material.textfield.TextInputEditText

class EditSequenceFragment : Fragment() {
    private lateinit var binding: FragmentEditSequenceBinding
    private val viewModel: TimerViewModel by viewModels()
    private var currentSequence: TimerSequence? = null

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?
    ): View {
        binding = FragmentEditSequenceBinding.inflate(inflater, container, false)

        val sequenceId = arguments?.getInt("sequence_id") ?: -1

        if (sequenceId != -1) {
            viewModel.getSequenceById(sequenceId).observe(viewLifecycleOwner) { sequence ->
                sequence?.let {
                    currentSequence = it
                    (binding.titleEditText as? TextInputEditText)?.setText(it.title ?: "")
                    (binding.workoutEditText as? TextInputEditText)?.setText(it.workout?.toString() ?: "")
                    (binding.warmUpEditText as? TextInputEditText)?.setText(it.warmUp?.toString() ?: "")
                    (binding.restEditText as? TextInputEditText)?.setText(it.rest?.toString() ?: "")
                    (binding.cooldownEditText as? TextInputEditText)?.setText(it.cooldown?.toString() ?: "")
                    (binding.repetitionsEditText as? TextInputEditText)?.setText(it.repetitions?.toString() ?: "")
                    (binding.colorEditText as? TextInputEditText)?.setText(it.color ?: "")
                    (binding.durationEditText as? TextInputEditText)?.setText(it.duration?.toString() ?: "")


                    // Показать клавиатуру после заполнения данных
                    binding.titleEditText.requestFocus()
                    showKeyboard(binding.titleEditText)
                }
            }
        }
        setupKeyboardHandling()

        binding.saveButton.setOnClickListener {
            val newSequence = TimerSequence(
                id = currentSequence?.id ?: 0,
                title = (binding.titleEditText as? TextInputEditText)?.text?.toString() ?: "",
                workout = (binding.workoutEditText as? TextInputEditText)?.text?.toString()?.toIntOrNull() ?: 0,
                warmUp = (binding.warmUpEditText as? TextInputEditText)?.text?.toString()?.toIntOrNull() ?: 0,
                rest = (binding.restEditText as? TextInputEditText)?.text?.toString()?.toIntOrNull() ?: 0,
                cooldown = (binding.cooldownEditText as? TextInputEditText)?.text?.toString()?.toIntOrNull() ?: 0,
                repetitions = (binding.repetitionsEditText as? TextInputEditText)?.text?.toString()?.toIntOrNull() ?: 1,
                color = (binding.colorEditText as? TextInputEditText)?.text?.toString() ?: "",
                duration = (binding.durationEditText as? TextInputEditText)?.text?.toString()?.toLongOrNull() ?: 0L
            )

            if (currentSequence == null) {
                viewModel.addSequence(newSequence)
            } else {
                viewModel.updateSequence(newSequence)
            }

            findNavController().popBackStack()
        }

        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        binding.titleEditText.requestFocus()
        showKeyboard(binding.titleEditText)
    }

    private fun setupKeyboardHandling() {
        val focusableViews = listOf(
            binding.titleEditText,
            binding.workoutEditText,
            binding.restEditText
        )

        focusableViews.forEach { editText ->
            editText.setOnFocusChangeListener { v, hasFocus ->
                if (hasFocus) showKeyboard(v)
            }
        }

        binding.root.setOnTouchListener { _, _ ->
            hideKeyboard()
            false
        }
    }

    private fun showKeyboard(view: View) {
        view.requestFocus()
        val imm = requireContext().getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
        imm.showSoftInput(view, InputMethodManager.SHOW_IMPLICIT)
    }

    private fun hideKeyboard() {
        val imm = requireContext().getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
        imm.hideSoftInputFromWindow(binding.root.windowToken, 0)
    }
}