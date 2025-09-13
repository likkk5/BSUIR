package com.example.tabatatimer.data

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity
data class TimerSequence(
    @PrimaryKey(autoGenerate = true) val id: Int = 0,
    val title: String,
    val color: String,
    val warmUp: Int,
    val workout: Int,
    val rest: Int,
    val cooldown: Int,
    val repetitions: Int,
    val duration: Long
)
