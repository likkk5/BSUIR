package common

import androidx.compose.foundation.layout.Box
import androidx.compose.material.Button
import androidx.compose.material.DropdownMenu
import androidx.compose.material.DropdownMenuItem
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.foundation.background
import androidx.compose.material.*

interface UnitConverter {
    fun toBaseValue(value: Double): Double
    fun fromBaseValue(value: Double): Double
}


enum class TemperatureUnit : UnitConverter {
    Celsius {
        override fun toBaseValue(value: Double) = value
        override fun fromBaseValue(value: Double) = value
    },
    Fahrenheit {
        override fun toBaseValue(value: Double) = (value - 32) * 5 / 9
        override fun fromBaseValue(value: Double) = value * 9 / 5 + 32
    },
    Kelvin {
        override fun toBaseValue(value: Double) = value - 273.15
        override fun fromBaseValue(value: Double) = value + 273.15
    }
}

enum class WeightUnit : UnitConverter {
    Kilograms {
        override fun toBaseValue(value: Double) = value
        override fun fromBaseValue(value: Double) = value
    },
    Pounds {
        override fun toBaseValue(value: Double) = value * 0.453592
        override fun fromBaseValue(value: Double) = value / 0.453592
    },
    Ounces {
        override fun toBaseValue(value: Double) = value * 0.0283495
        override fun fromBaseValue(value: Double) = value / 0.0283495
    }
}

enum class DistanceUnit : UnitConverter {
    Meters {
        override fun toBaseValue(value: Double) = value
        override fun fromBaseValue(value: Double) = value
    },
    Kilometers {
        override fun toBaseValue(value: Double) = value * 1000
        override fun fromBaseValue(value: Double) = value / 1000
    },
    Miles {
        override fun toBaseValue(value: Double) = value * 1609.34
        override fun fromBaseValue(value: Double) = value / 1609.34
    },
    Yards {
        override fun toBaseValue(value: Double) = value * 0.9144
        override fun fromBaseValue(value: Double) = value / 0.9144
    }
}


@Composable
fun <T : UnitConverter> UnitDropdown(
    selectedUnit: T,
    onUnitSelected: (T) -> Unit,
    units: Array<T>
) {
    var expanded by remember { mutableStateOf(false) }

    Box {
        Button(
            onClick = { expanded = true },
            colors = ButtonDefaults.buttonColors(backgroundColor = Color(0xFF0A3D91)) // Темно-синий цвет кнопки
        ) {
            Text(selectedUnit.toString(), color = Color.White)
        }
        DropdownMenu(
            expanded = expanded,
            onDismissRequest = { expanded = false },
            modifier = Modifier.background(Color(0xFF37474F)) // Темно-серый фон выпадающего списка
        ) {
            units.forEach { unit ->
                DropdownMenuItem(onClick = {
                    onUnitSelected(unit)
                    expanded = false
                }) {
                    Text(unit.toString(), color = Color.White)
                }
            }
        }
    }
}