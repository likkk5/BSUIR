package navigation

sealed interface HomeScreenEvent {
    data object ClickWeightConverter: HomeScreenEvent
    data object ClickDistanceConverter: HomeScreenEvent
    data object ClickTemperatureConverter: HomeScreenEvent
}