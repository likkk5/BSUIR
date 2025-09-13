package com.example.tabatatimer

import android.os.Bundle
import android.view.Menu
import android.view.MenuItem
import androidx.appcompat.widget.Toolbar
import androidx.appcompat.app.AppCompatActivity
import androidx.appcompat.app.AppCompatDelegate
import androidx.navigation.findNavController
import androidx.navigation.fragment.NavHostFragment
import androidx.preference.PreferenceManager
import java.util.Locale

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        applyTheme() // Применяем тему до super.onCreate()
        applyLocale() // Применяем язык до super.onCreate()

        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val toolbar = findViewById<Toolbar>(R.id.toolbar)
        setSupportActionBar(toolbar)

        if (savedInstanceState == null) {
            val navHostFragment =
                supportFragmentManager.findFragmentById(R.id.fragment_container) as? NavHostFragment
                    ?: return
            val navController = navHostFragment.navController
        }
    }

    fun applyTheme() {
        val sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this)
        //when (sharedPreferences.getString("font_size", "medium")) {
           // "small" -> setTheme(R.style.FontSizeSmall)
           // "medium" -> setTheme(R.style.FontSizeMedium)
           // "large" -> setTheme(R.style.FontSizeLarge)
        //}
        val fontScale = when (sharedPreferences.getString("font_size", "medium")) {
            "small" -> 0.9f
            "medium" -> 1.2f
            "large" -> 1.5f
            else -> 1.2f
        }

        val config = resources.configuration
        if (config.fontScale != fontScale) {
            config.fontScale = fontScale
            resources.updateConfiguration(config, resources.displayMetrics)
        }
        val isDarkMode = sharedPreferences.getBoolean("dark_mode", false)
        AppCompatDelegate.setDefaultNightMode(
            if (isDarkMode) AppCompatDelegate.MODE_NIGHT_YES
            else AppCompatDelegate.MODE_NIGHT_NO
        )
    }

    fun applyLocale() {
        val sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this)
        val selectedLanguage = sharedPreferences.getString("language", "ru") ?: "en"

        val locale = Locale(selectedLanguage)
        Locale.setDefault(locale)

        val config = resources.configuration
        config.setLocale(locale)
        config.setLayoutDirection(locale)

        val context = createConfigurationContext(config)
        resources.updateConfiguration(config, context.resources.displayMetrics)
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.main_menu, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            R.id.action_settings -> {
                findNavController(R.id.fragment_container).navigate(R.id.settingsFragment)
                true
            }
            else -> super.onOptionsItemSelected(item)
        }
    }
}
