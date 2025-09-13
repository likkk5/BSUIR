package com.example.tabatatimer.ui.screens

import android.os.Bundle
import androidx.preference.*
import com.example.tabatatimer.MainActivity
import com.example.tabatatimer.R

class SettingsFragment : PreferenceFragmentCompat() {

    override fun onCreatePreferences(savedInstanceState: Bundle?, rootKey: String?) {
        setPreferencesFromResource(R.xml.preferences, rootKey)

        val fontSizePref = findPreference<ListPreference>("font_size")
        fontSizePref?.setOnPreferenceChangeListener { _, _ ->
            (requireActivity() as MainActivity).applyTheme()
            requireActivity().recreate() // Перезапуск для применения темы
            true
        }

        val languagePref = findPreference<ListPreference>("language")
        languagePref?.setOnPreferenceChangeListener { _, _ ->
            (requireActivity() as MainActivity).applyLocale()
            restartApp() // Полный перезапуск для смены языка
            true
        }

        val darkModePref = findPreference<SwitchPreferenceCompat>("dark_mode")
        darkModePref?.setOnPreferenceChangeListener { _, _ ->
            (requireActivity() as MainActivity).applyTheme()
            requireActivity().recreate()
            true
        }
    }

    private fun restartApp() {
        val intent = requireActivity().intent
        requireActivity().finish()
        requireActivity().overridePendingTransition(0, 0)
        requireActivity().startActivity(intent)
    }
}
