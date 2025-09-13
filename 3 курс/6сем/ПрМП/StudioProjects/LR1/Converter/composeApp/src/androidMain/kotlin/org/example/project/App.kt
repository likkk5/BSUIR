package org.example.project

import androidx.compose.material.MaterialTheme
import androidx.compose.runtime.*
import com.arkivanov.decompose.extensions.compose.jetbrains.stack.Children
import com.arkivanov.decompose.extensions.compose.jetbrains.stack.animation.slide
import com.arkivanov.decompose.extensions.compose.jetbrains.stack.animation.stackAnimation
import com.arkivanov.decompose.extensions.compose.jetbrains.subscribeAsState
import org.jetbrains.compose.ui.tooling.preview.Preview

import navigation.RootComponent
import screens.DistanceConverterScreen
import screens.HomeScreen
import screens.TemperatureConverterScreen
import screens.WeightConverterScreen

@Composable
@Preview
fun App(root:RootComponent) {
    MaterialTheme {
        val childStack by root.childStack.subscribeAsState()
        Children(
            stack = childStack,
            animation = stackAnimation(slide())
        ) { child ->
            when(val instance = child.instance) {
                is RootComponent.Child.HomeScreen -> HomeScreen(instance.component)
                is RootComponent.Child.WeightConverterScreen -> WeightConverterScreen(instance.component)
                is RootComponent.Child.DistanceConverterScreen -> DistanceConverterScreen(instance.component)
                is RootComponent.Child.TemperatureConverterScreen -> TemperatureConverterScreen(instance.component)
            }
        }
    }
}