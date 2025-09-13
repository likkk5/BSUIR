package com.example.tabatatimer.ui.adapters

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.RecyclerView
import com.example.tabatatimer.databinding.ItemTimerBinding
import com.example.tabatatimer.data.TimerSequence
import androidx.navigation.fragment.findNavController

class TimerAdapter(private var sequences: List<TimerSequence>) : RecyclerView.Adapter<TimerAdapter.TimerViewHolder>() {

    var onDeleteClickListener: ((TimerSequence) -> Unit)? = null
    var onEditClickListener: ((TimerSequence) -> Unit)? = null
    var onStartClickListener: ((TimerSequence) -> Unit)? = null  // Новый обработчик

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): TimerViewHolder {
        val binding = ItemTimerBinding.inflate(LayoutInflater.from(parent.context), parent, false)
        return TimerViewHolder(binding)
    }

    override fun onBindViewHolder(holder: TimerViewHolder, position: Int) {
        val sequence = sequences[position]
        holder.bind(sequence)

        holder.binding.editButton.setOnClickListener {
            onEditClickListener?.invoke(sequence)
        }

        holder.binding.deleteButton.setOnClickListener {
            onDeleteClickListener?.invoke(sequence)
        }

        holder.binding.startTimerButton.setOnClickListener {
            onStartClickListener?.invoke(sequence)  // Запуск таймера
        }
    }

    override fun getItemCount(): Int = sequences.size

    fun updateData(newSequences: List<TimerSequence>) {
        sequences = newSequences
        notifyDataSetChanged()
    }

    class TimerViewHolder(val binding: ItemTimerBinding) : RecyclerView.ViewHolder(binding.root) {
        fun bind(sequence: TimerSequence) {
            binding.textView.text = sequence.title

            val color = sequence.color?.takeIf { it.isNotBlank() } ?: "#808080" // Серый по умолчанию
            try {
                binding.colorIndicator?.setBackgroundColor(android.graphics.Color.parseColor(color))
            } catch (e: IllegalArgumentException) {
                binding.colorIndicator?.setBackgroundColor(android.graphics.Color.GRAY) // Если цвет невалидный
            }
        }
    }

}
