package screens

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.*
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import navigation.HomeScreenComponent
import navigation.HomeScreenEvent

@Composable
fun HomeScreen(component: HomeScreenComponent) {
    Column(
        modifier = Modifier
            .fillMaxSize()
            .background(Color(0xFFE3F2FD))
            .padding(16.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center
    ) {
        Text("Choose any converter", fontSize = 24.sp, color = Color(0xFF0D47A1))

        Spacer(modifier = Modifier.height(16.dp))

        Button(
            onClick = { component.onEvent(HomeScreenEvent.ClickDistanceConverter) },
            modifier = Modifier.fillMaxWidth(),
            shape = RoundedCornerShape(8.dp),
            colors = ButtonDefaults.buttonColors(backgroundColor = Color(0xFF64B5F6))
        ) {
            Text("Distance Converter", color = Color.White, fontSize = 18.sp)
        }

        Spacer(modifier = Modifier.height(16.dp))

        Button(
            onClick = { component.onEvent(HomeScreenEvent.ClickWeightConverter) },
            modifier = Modifier.fillMaxWidth(),
            shape = RoundedCornerShape(8.dp),
            colors = ButtonDefaults.buttonColors(backgroundColor = Color(0xFF1E88E5))
        ) {
            Text("Weight Converter", color = Color.White, fontSize = 18.sp)
        }

        Spacer(modifier = Modifier.height(16.dp))

        Button(
            onClick = { component.onEvent(HomeScreenEvent.ClickTemperatureConverter) },
            modifier = Modifier.fillMaxWidth(),
            shape = RoundedCornerShape(8.dp),
            colors = ButtonDefaults.buttonColors(backgroundColor = Color(0xFF0A3D91))
        ) {
            Text("Temperature Converter", color = Color.White, fontSize = 18.sp)
        }
    }
}
