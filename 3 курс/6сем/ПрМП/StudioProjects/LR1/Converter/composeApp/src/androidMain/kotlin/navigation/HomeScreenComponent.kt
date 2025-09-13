package navigation

import com.arkivanov.decompose.ComponentContext

class HomeScreenComponent(
    componentContext: ComponentContext,
    private val onNavigateToWeightConverter: () -> Unit,
    private val onNavigateToDistanceConverter: () -> Unit,
    private val onNavigateToTemperatureConverter: () -> Unit,
):ComponentContext by componentContext {


    fun onEvent(event: HomeScreenEvent) {
        when(event) {
            HomeScreenEvent.ClickWeightConverter -> onNavigateToWeightConverter()
            HomeScreenEvent.ClickDistanceConverter->onNavigateToDistanceConverter()
            HomeScreenEvent.ClickTemperatureConverter->onNavigateToTemperatureConverter()
        }
    }
}