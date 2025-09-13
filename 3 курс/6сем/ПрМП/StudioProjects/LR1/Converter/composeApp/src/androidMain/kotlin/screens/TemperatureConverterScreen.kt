package screens

import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.*
import androidx.navigation.compose.NavHost
import androidx.navigation.compose.composable
import androidx.navigation.compose.rememberNavController
import common.DataFragment
import common.KeyboardFragment
import common.TemperatureUnit
import navigation.TemperatureConverterComponent

@Composable
fun TemperatureConverterScreen(component: TemperatureConverterComponent) {
    var inputValue by remember { mutableStateOf("") }
    var fromUnit by remember { mutableStateOf(TemperatureUnit.Celsius) }
    var toUnit by remember { mutableStateOf(TemperatureUnit.Fahrenheit) }
    var result by remember { mutableStateOf("") }

    val navController = rememberNavController()

    NavHost(navController, startDestination = "dataFragment") {
        composable("dataFragment") {
            DataFragment(
                inputValue = inputValue,
                fromUnit = fromUnit,
                toUnit = toUnit,
                result = result,
                onConvert = {
                    val number = inputValue.toDoubleOrNull()
                    if (number == null) {
                        result = "Enter a valid number"
                    } else {
                        val baseValue = fromUnit.toBaseValue(number)
                        result = toUnit.fromBaseValue(baseValue).toString()
                    }
                },
                onUnitSelected = { unit, isFromUnit ->
                    if (isFromUnit) fromUnit = unit else toUnit = unit
                },
                onNavigateToKeyboard = { navController.navigate("keyboardFragment") },
                units = TemperatureUnit.values(),
                onGoBack = { component.goBack() }
            )
        }
        composable("keyboardFragment") {
            KeyboardFragment(
                onNumberClick = { number ->
                    inputValue = inputValue + number
                },
                onClear = {
                    inputValue = ""
                    result = ""
                },
                onBack = { navController.popBackStack() }
            )
        }
    }
}

