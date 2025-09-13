package com.example.calculator.fragments

import android.content.Context
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import com.example.calculator.calculations.Calculator
import com.example.calculator.calculations.Operations
import android.widget.TextView
import com.example.calculator.R
import com.example.calculator.MainActivity
import com.example.calculator.Connector

import kotlin.math.*


class ScienceModeFragment : Fragment() {
    private lateinit var btn_sin: Button
    private lateinit var btn_cos: Button
    private lateinit var btn_tan: Button
    private lateinit var btn_rad: Button
    private lateinit var btn_sqrt: Button
    private lateinit var btn_ln: Button
    private lateinit var btn_lg: Button
    private lateinit var btn_log: Button
    private lateinit var btn_powerMinOne: Button
    private lateinit var btn_expPowX: Button
    private lateinit var btn_square: Button
    private lateinit var btn_power: Button
    private lateinit var btn_module: Button
    private lateinit var btn_pi: Button
    private lateinit var btn_exp: Button

    private lateinit var calculator : Calculator
    var mainActivity = activity as? MainActivity

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        val view: View = inflater.inflate(R.layout.fragment_science_mode, container, false)
        setupLayoutFor(view)
        return view
    }

    private fun setupLayoutFor(view: View) {
        btn_sin = view.findViewById((R.id.btn_sin))
        btn_sin.setOnClickListener{
            BaseModeFragment.stringList.add("sin(")
            calculator.appendFunction("sin(") { n1 : Double -> (sin(n1)) }
        }
        btn_cos = view.findViewById((R.id.btn_cos))
        btn_cos.setOnClickListener{
            BaseModeFragment.stringList.add("cos(")
            calculator.appendFunction("cos(") { n1 : Double -> (cos(n1)) }
        }
        btn_tan = view.findViewById((R.id.btn_tan))
        btn_tan.setOnClickListener{
            BaseModeFragment.stringList.add("tan(")
            calculator.appendFunction("tan(") { n1 : Double -> (tan(n1)) }
        }
        btn_rad = view.findViewById((R.id.btn_rad))
        btn_rad.setOnClickListener{
            BaseModeFragment.stringList.add("rad(")
            calculator.appendFunction("rad(") { n1 : Double -> (Math.toRadians(n1)) }
        }
        btn_sqrt = view.findViewById((R.id.btn_sqrt))
        btn_sqrt.setOnClickListener{
            BaseModeFragment.stringList.add("sqrt(")
            calculator.appendFunction("sqrt(") { n1 : Double -> (sqrt(n1)) }
        }
        btn_ln = view.findViewById((R.id.btn_ln))
        btn_ln.setOnClickListener{
            BaseModeFragment.stringList.add("ln(")
            calculator.appendFunction("ln(") { n1 : Double -> (ln(n1)) }
        }
        btn_log = view.findViewById((R.id.btn_log))
        btn_log.setOnClickListener{
            BaseModeFragment.stringList.add("log(")
            calculator.appendFunction("log(") { n1 : Double -> (log2(n1)) }
        }
        btn_lg = view.findViewById((R.id.btn_lg))
        btn_lg.setOnClickListener{
            BaseModeFragment.stringList.add("lg(")
            calculator.appendFunction("lg(") { n1 : Double -> (log10(n1)) }
        }
        btn_powerMinOne = view.findViewById((R.id.btn_powerMinOne))
        btn_powerMinOne.setOnClickListener{
            BaseModeFragment.stringList.add("1/(")
            calculator.appendFunction("(1/(") { n1 : Double -> (1 / n1) }
        }
        btn_expPowX = view.findViewById((R.id.btn_expPowX))
        btn_expPowX.setOnClickListener{
            BaseModeFragment.stringList.add("e^(")
            calculator.appendFunction("e^(") { n1 : Double -> (exp(n1)) }
        }
        btn_square = view.findViewById((R.id.btn_square))
        btn_square.setOnClickListener{
            calculator.appendOperation(Operations.POWER)
            val textView = mainActivity?.getinputText()
            calculator.appendNumber("2")
            BaseModeFragment.stringList.add("^2(")
            if(textView?.text.toString() == "2"){
                calculator.delete()
                if (BaseModeFragment.stringList.isNotEmpty()) {
                    BaseModeFragment.stringList.removeAt(BaseModeFragment.stringList.size - 1)
                }
            }

        }
        btn_power = view.findViewById((R.id.btn_power))
        btn_power.setOnClickListener{
            calculator.appendOperation(Operations.POWER)
        }
        btn_module = view.findViewById((R.id.btn_module))
        btn_module.setOnClickListener{
            calculator.appendFunction("abs(") { n1 : Double -> (abs(n1)) }
        }
        btn_pi = view.findViewById((R.id.btn_pi))
        btn_pi.setOnClickListener{
            calculator.appendNumber("π")
        }
        btn_exp = view.findViewById((R.id.btn_exp))
        btn_exp.setOnClickListener{
            calculator.appendNumber("e")
        }

        this.calculator = activ!!.getCalculator()
    }

    var activ: Connector? = null  //ссылка на MainActivity

    fun getInstance(): BaseModeFragment? {
        val args = Bundle()
        val fragment = BaseModeFragment()
        fragment.setArguments(args)
        return fragment
    }

    override fun onAttach(context: Context) {
        super.onAttach(context)
        activ = getActivity() as Connector?
        if (context is MainActivity) {
            mainActivity = context
        }
    }
}