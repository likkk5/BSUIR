package navigation

import com.arkivanov.decompose.ComponentContext
import com.arkivanov.decompose.router.stack.StackNavigation
import com.arkivanov.decompose.router.stack.childStack
import com.arkivanov.decompose.router.stack.pop
import com.arkivanov.decompose.router.stack.pushNew
import kotlinx.serialization.Serializable

class RootComponent(
    componentContext: ComponentContext
) :ComponentContext by componentContext {

    private val navigation = StackNavigation<Configuration>()

    val childStack = childStack(
        source = navigation,
        serializer = Configuration.serializer(),
        initialConfiguration = Configuration.HomeScreen,
        handleBackButton = true,
        childFactory = ::createChild
    )


    private fun createChild(
        config:Configuration,
        context: ComponentContext
    ):Child{
        return when(config){
            Configuration.HomeScreen -> Child.HomeScreen(
                HomeScreenComponent(
                    componentContext = context,
                    onNavigateToWeightConverter = {
                        navigation.pushNew(Configuration.WeightConverterScreen)
                    },
                    onNavigateToDistanceConverter={
                        navigation.pushNew(Configuration.DistanceConverterScreen)
                    },
                    onNavigateToTemperatureConverter = {
                        navigation.pushNew(Configuration.TemperatureConverterScreen) // MODIFY
                    })
            )
            is Configuration.WeightConverterScreen -> Child.WeightConverterScreen(
                WeightConverterComponent(
                    componentContext = context,
                    onGoBack = {
                        navigation.pop()
                    })
            )
            is Configuration.DistanceConverterScreen -> Child.DistanceConverterScreen(
                DistanceConverterComponent(
                    componentContext = context,
                    onGoBack = {
                        navigation.pop()
                    })
            )
            is Configuration.TemperatureConverterScreen -> Child.TemperatureConverterScreen(
                TemperatureConverterComponent(
                    componentContext = context,
                    onGoBack = {
                        navigation.pop()
                    })
            )
        }
    }

    sealed class Child{
        data class HomeScreen(val component: HomeScreenComponent):Child()
        data class WeightConverterScreen(val component: WeightConverterComponent):Child()
        data class DistanceConverterScreen(val component: DistanceConverterComponent):Child()
        data class TemperatureConverterScreen(val component: TemperatureConverterComponent):Child()
    }

    @Serializable
    sealed class Configuration{
        @Serializable
        data object HomeScreen: Configuration()

        @Serializable
        data object WeightConverterScreen: Configuration()

        @Serializable
        data object DistanceConverterScreen: Configuration()

        @Serializable
        data object TemperatureConverterScreen: Configuration()
    }
}