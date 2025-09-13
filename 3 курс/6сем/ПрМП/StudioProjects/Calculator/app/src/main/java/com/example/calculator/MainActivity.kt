package com.example.calculator

import android.annotation.SuppressLint
import android.content.Context
import android.content.Intent
import android.content.pm.ActivityInfo
import android.content.pm.PackageManager
import android.content.res.Configuration
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.os.Bundle
import android.os.Vibrator
import android.preference.PreferenceManager
import android.text.method.ScrollingMovementMethod
import android.view.GestureDetector
import android.view.MotionEvent
import android.view.View
import android.widget.Button
import android.widget.Switch
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.core.content.ContextCompat
import androidx.core.view.GestureDetectorCompat
import androidx.fragment.app.FragmentContainerView
import com.example.calculator.Connector
import com.example.calculator.R
import com.example.calculator.calculations.Calculator
import com.example.calculator.calculations.Operations


class MainActivity : AppCompatActivity(), Connector, SensorEventListener {


    private var sensorManager: SensorManager? = null
    private var accelerometer: Sensor? = null
    private var lastTime: Long = 0
    private var lastX: Float = 0.0f
    private var lastY: Float = 0.0f
    private var lastZ: Float = 0.0f
    private val shakeThreshold = 600

    companion object {
        private var calculator = Calculator()

        private const val SWIPE_MIN_DISTANCE = 130
        private const val SWIPE_MAX_DISTANCE = 300
        private const val SWIPE_MIN_VELOCITY = 200
    }

    lateinit var inputText : TextView
    private lateinit var resultText : TextView
    private lateinit var btn_2nd: Button

    private lateinit var lSwipeDetector: GestureDetectorCompat
    private lateinit var mainLayout: ConstraintLayout


    private fun changeMode() {
        val currentOrientation = resources.configuration.orientation
        val modeSwitch: Switch = findViewById(R.id.modeSwitch)
        val baseFragment: FragmentContainerView = findViewById(R.id.baseModeFragment)
        val scienceFragment: FragmentContainerView = findViewById(R.id.scienceModeFragment)

        if (currentOrientation == Configuration.ORIENTATION_PORTRAIT) {
            requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
            modeSwitch.isChecked = true // Включаем научный режим
            baseFragment.visibility = View.VISIBLE
            scienceFragment.visibility = View.VISIBLE
        } else {
            requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_PORTRAIT
            modeSwitch.isChecked = false // Возвращаем обычный режим
            baseFragment.visibility = View.VISIBLE
            scienceFragment.visibility = View.GONE
        }
    }

    @SuppressLint("ClickableViewAccessibility")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        if (isDemo()) {
            val scienceFragment: FragmentContainerView = findViewById(R.id.scienceModeFragment)
            scienceFragment.visibility = View.GONE // Скрываем научный режим
        }

        inputText = findViewById(R.id.textViewInput)
        resultText = findViewById(R.id.textViewResult)
        calculator.setListeners(inputText, resultText)

        mainLayout = findViewById(R.id.science)
        val modeSwitch: Switch = findViewById(R.id.modeSwitch)
        val baseFragment: FragmentContainerView = findViewById(R.id.baseModeFragment)
        val scienceFragment: FragmentContainerView = findViewById(R.id.scienceModeFragment)

        modeSwitch.setOnCheckedChangeListener { _, isChecked ->
            if (!isDemo()) {
                if (isChecked) {
                    baseFragment.visibility = View.VISIBLE  // Показываем обычный режим
                    scienceFragment.visibility = View.VISIBLE // Показываем научный режим
                } else {
                    baseFragment.visibility = View.VISIBLE  // Оставляем обычный режим
                    scienceFragment.visibility = View.GONE  // Скрываем научный режим
                }
            } else {
                Toast.makeText(this, "Scientific mode is available only in full version", Toast.LENGTH_SHORT).show()
                modeSwitch.isChecked = false // Запрещаем включение
            }
        }

        btn_2nd = findViewById(R.id.btn_2nd)
        btn_2nd.setOnClickListener {
            if (isDemo()) {
                // Только меняем ориентацию, но режим остаётся обычным
                val currentOrientation = resources.configuration.orientation
                requestedOrientation = if (currentOrientation == Configuration.ORIENTATION_PORTRAIT) {
                    ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
                } else {
                    ActivityInfo.SCREEN_ORIENTATION_PORTRAIT
                }
                Toast.makeText(this, "Scientific mode is available only in full version", Toast.LENGTH_SHORT).show()
            } else {
                // В полной версии меняем ориентацию + включаем Science Mode
                changeMode()
            }
        }


        btn_2nd.bringToFront()

        inputText.movementMethod = ScrollingMovementMethod()

        lSwipeDetector = GestureDetectorCompat(this, MyGestureListener())

        mainLayout.setOnTouchListener { _, event ->
            lSwipeDetector.onTouchEvent(event)
            true
        }

        sensorManager = getSystemService(Context.SENSOR_SERVICE) as SensorManager
        accelerometer = sensorManager?.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)
        sensorManager?.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_NORMAL)
    }


    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {
        // Не требуется реализация
    }

    override fun onSensorChanged(event: SensorEvent?) {
        if (event?.sensor?.type == Sensor.TYPE_ACCELEROMETER) {
            val currentTime = System.currentTimeMillis()
            val diffTime = currentTime - lastTime
            if (diffTime > 100) {
                val x = event.values[0]
                val y = event.values[1]
                val z = event.values[2]
                val speed = Math.abs(x + y + z - lastX - lastY - lastZ) / diffTime * 10000
                if (speed > shakeThreshold) {
                    onShake()
                }
                lastX = x
                lastY = y
                lastZ = z
                lastTime = currentTime
            }
        }
    }

    private fun onShake() {
        Toast.makeText(this, "Device shook! Clearing!", Toast.LENGTH_SHORT).show()
        calculator.clear()
    }

    override fun onResume() {
        super.onResume()
        sensorManager?.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_NORMAL)
    }

    override fun onPause() {
        super.onPause()
        sensorManager?.unregisterListener(this)
    }

    inner class MyGestureListener : GestureDetector.SimpleOnGestureListener() {
        override fun onDown(e: MotionEvent): Boolean {
            return true
        }

        override fun onFling(
            e1: MotionEvent?,
            e2: MotionEvent,
            velocityX: Float,
            velocityY: Float
        ): Boolean {
            val deltaX = e2.x - e1!!.x
            val deltaY = e2.y - e1.y
            val deltaXAbs = Math.abs(deltaX)
            val deltaYAbs = Math.abs(deltaY)

            if (deltaXAbs > SWIPE_MIN_DISTANCE && Math.abs(velocityX) > SWIPE_MIN_VELOCITY) {
                if (deltaX > 0) {
                    calculator.appendOperation(Operations.ADD)
                    //Toast.makeText(this@MainActivity, "Swipe Right", Toast.LENGTH_SHORT).show()
                } else {
                    calculator.appendOperation(Operations.SUBTRACT)
                    //Toast.makeText(this@MainActivity, "Swipe Left", Toast.LENGTH_SHORT).show()
                }
                return true
            }

            if (deltaYAbs > SWIPE_MIN_DISTANCE && Math.abs(velocityY) > SWIPE_MIN_VELOCITY) {
                if (deltaY > 0) {
                    calculator.appendOperation(Operations.DIVIDE)
                    //Toast.makeText(this@MainActivity, "Swipe Down", Toast.LENGTH_SHORT).show()
                } else {
                    calculator.appendOperation(Operations.MULTIPLY)
                    //Toast.makeText(this@MainActivity, "Swipe Up", Toast.LENGTH_SHORT).show()
                }
                return true
            }

            return false
        }
    }

    fun getinputText(): TextView {
        return inputText
    }

    override fun getCalculator(): Calculator { //Interface function
        return calculator
    }

    override fun isDemo(): Boolean {
        return applicationContext.packageName.endsWith(".demo")
    }

}