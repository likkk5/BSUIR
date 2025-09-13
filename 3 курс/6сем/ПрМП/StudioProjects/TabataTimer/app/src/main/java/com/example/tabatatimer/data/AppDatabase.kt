package com.example.tabatatimer.data

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import androidx.room.migration.Migration
import androidx.sqlite.db.SupportSQLiteDatabase

@Database(entities = [TimerSequence::class], version = 2)  // Увеличьте версию
abstract class AppDatabase : RoomDatabase() {
    abstract fun timerDao(): TimerDao

    companion object {
        @Volatile private var instance: AppDatabase? = null

        // Миграция из версии 1 в версию 2, чтобы добавить новое поле `duration`
        val MIGRATION_1_2 = object : Migration(1, 2) {
            override fun migrate(database: SupportSQLiteDatabase) {
                // Добавляем новое поле в таблицу TimerSequence
                database.execSQL("ALTER TABLE TimerSequence ADD COLUMN duration INTEGER NOT NULL DEFAULT 0")
            }
        }

        fun getDatabase(context: Context): AppDatabase {
            return instance ?: synchronized(this) {
                val newInstance = Room.databaseBuilder(
                    context.applicationContext,
                    AppDatabase::class.java,
                    "timer_database"
                )
                    .addMigrations(MIGRATION_1_2)  // Добавляем миграцию
                    .build()
                instance = newInstance
                newInstance
            }
        }
    }
}
