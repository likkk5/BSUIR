package common

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.*
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp

@Composable
fun <T : UnitConverter> DataFragment(
    inputValue: String,
    fromUnit: T,
    toUnit: T,
    result: String,
    onConvert: () -> Unit,
    onUnitSelected: (T, Boolean) -> Unit,
    onNavigateToKeyboard: () -> Unit,
    units: Array<T>,
    onGoBack: () -> Unit
) {
    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(16.dp)
            .background(Color(0xFFE3F2FD)),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Text(text = "Unit Converter", fontSize = 24.sp, fontWeight = FontWeight.Bold, color = Color(0xFF0D47A1))

        Spacer(modifier = Modifier.height(16.dp))

        Card(
            modifier = Modifier.fillMaxWidth(),
            shape = RoundedCornerShape(12.dp),
            backgroundColor = Color(0xFFBBDEFB)
        ) {
            Column(modifier = Modifier.padding(16.dp)) {
                Text(text = "Enter value", fontSize = 16.sp, color = Color(0xFF0D47A1))
                TextField(
                    value = inputValue,
                    onValueChange = {},
                    modifier = Modifier.fillMaxWidth(),
                    readOnly = true,
                    colors = TextFieldDefaults.textFieldColors(backgroundColor = Color.White)
                )
            }
        }

        Spacer(modifier = Modifier.height(16.dp))

        Row(verticalAlignment = Alignment.CenterVertically) {
            UnitDropdown(selectedUnit = fromUnit, onUnitSelected = { unit -> onUnitSelected(unit, true) }, units = units)
            Spacer(modifier = Modifier.width(8.dp))
            Text(text = "to", fontSize = 18.sp, color = Color(0xFF0D47A1))
            Spacer(modifier = Modifier.width(8.dp))
            UnitDropdown(selectedUnit = toUnit, onUnitSelected = { unit -> onUnitSelected(unit, false) }, units = units)
        }

        Spacer(modifier = Modifier.height(16.dp))

        Button(
            onClick = { onConvert() },
            modifier = Modifier.fillMaxWidth(),
            shape = RoundedCornerShape(8.dp),
            colors = ButtonDefaults.buttonColors(backgroundColor = Color(0xFF64B5F6))
        ) {
            Text("Convert", color = Color.White, fontSize = 18.sp, fontWeight = FontWeight.Bold)
        }

        Spacer(modifier = Modifier.height(16.dp))

        Card(
            modifier = Modifier.fillMaxWidth(),
            shape = RoundedCornerShape(12.dp),
            backgroundColor = Color(0xFFBBDEFB)
        ) {
            Column(modifier = Modifier.padding(16.dp)) {
                Text(text = "Result", fontSize = 16.sp, color = Color(0xFF0D47A1))
                Text(text = result, fontSize = 20.sp, fontWeight = FontWeight.Bold, color = Color.Black)
            }
        }

        Spacer(modifier = Modifier.height(32.dp))

        Button(
            onClick = { onNavigateToKeyboard() },
            modifier = Modifier.fillMaxWidth(),
            shape = RoundedCornerShape(8.dp),
            colors = ButtonDefaults.buttonColors(backgroundColor = Color(0xFF1E88E5))
        ) {
            Text("Open Keyboard", color = Color.White, fontSize = 18.sp, fontWeight = FontWeight.Bold)
        }

        Spacer(modifier = Modifier.height(16.dp))

        OutlinedButton(
            onClick = { onGoBack() },
            modifier = Modifier.fillMaxWidth(),
            shape = RoundedCornerShape(8.dp),
            colors = ButtonDefaults.outlinedButtonColors(contentColor = Color(0xFF0D47A1))
        ) {
            Text("Go Back to Home Page", fontSize = 18.sp, fontWeight = FontWeight.Bold)
        }
    }
}
