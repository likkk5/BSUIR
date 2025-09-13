package com.example.tabatatimer.ui.screens

import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import androidx.fragment.app.viewModels
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.tabatatimer.viewmodel.TimerViewModel
import com.example.tabatatimer.databinding.FragmentHomeBinding
import android.view.LayoutInflater
import android.view.ViewGroup
import android.view.View
import androidx.navigation.fragment.findNavController
import com.example.tabatatimer.ui.adapters.TimerAdapter
import com.example.tabatatimer.R

class HomeFragment : Fragment() {
    private lateinit var binding: FragmentHomeBinding
    private val viewModel: TimerViewModel by viewModels()
    private lateinit var adapter: TimerAdapter

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?
    ): View {
        binding = FragmentHomeBinding.inflate(inflater, container, false)

        binding.recyclerView.layoutManager = LinearLayoutManager(context)
        adapter = TimerAdapter(emptyList()).apply {
            onStartClickListener = { sequence ->
                val bundle = Bundle().apply { putInt("sequence_id", sequence.id) }
                findNavController().navigate(R.id.action_homeFragment_to_timerFragment, bundle)
            }
            onDeleteClickListener = { sequence ->
                viewModel.deleteSequence(sequence)
                Log.d("HomeFragment", "Удалён таймер: ${sequence.title}")
            }
            onEditClickListener = { sequence ->
                val bundle = Bundle().apply { putInt("sequence_id", sequence.id) }
                findNavController().navigate(R.id.action_homeFragment_to_editSequenceFragment, bundle)
            }
        }
        binding.recyclerView.adapter = adapter

        viewModel.sequences.observe(viewLifecycleOwner) { sequences ->
            Log.d("HomeFragment", "Данные из БД: ${sequences.size} элементов")
            if (sequences.isNullOrEmpty()) {
                Log.w("HomeFragment", "Нет данных в БД! Добавляю тестовые данные.")
                viewModel.insertTestData()
            } else {
                adapter.updateData(sequences)
            }
        }

        viewModel.loadSequences()

        viewModel.isDataInserted.observe(viewLifecycleOwner) { isInserted ->
            if (isInserted) {
                Log.d("HomeFragment", "Данные успешно добавлены в базу")
            } else {
                Log.d("HomeFragment", "База данных уже содержит данные")
            }
        }

        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        binding.addButton?.setOnClickListener {
            val navController = findNavController()
            val bundle = Bundle().apply { putInt("sequence_id", -1) }
            navController.navigate(R.id.action_homeFragment_to_editSequenceFragment, bundle)
        }
    }
}
