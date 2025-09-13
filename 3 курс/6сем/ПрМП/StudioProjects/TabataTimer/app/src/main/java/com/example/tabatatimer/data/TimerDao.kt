package com.example.tabatatimer.data

import androidx.lifecycle.LiveData
import androidx.room.*

@Dao
interface TimerDao {
    @Query("SELECT * FROM TimerSequence")
    fun getAll(): LiveData<List<TimerSequence>>

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insert(sequence: TimerSequence)  // Теперь suspend

    @Update
    suspend fun update(sequence: TimerSequence)  // Теперь suspend

    @Delete
    suspend fun delete(sequence: TimerSequence)  // Теперь suspend

    @Query("DELETE FROM TimerSequence")
    suspend fun deleteAll()  // Теперь suspend

    @Query("SELECT * FROM TimerSequence WHERE id = :id LIMIT 1")
    fun getSequenceById(id: Int): LiveData<TimerSequence>
}
