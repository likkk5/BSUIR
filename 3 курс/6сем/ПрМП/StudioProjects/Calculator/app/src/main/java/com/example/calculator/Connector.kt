package com.example.calculator

import com.example.calculator.calculations.Calculator


// Нужен для получения фрагментом ссылки на экземпляр класса Calculator из MainActivity.
interface Connector {
    fun getCalculator() : Calculator
    fun isDemo() : Boolean
}