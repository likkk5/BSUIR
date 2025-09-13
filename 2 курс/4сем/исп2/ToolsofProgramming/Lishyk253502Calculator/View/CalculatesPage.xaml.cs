namespace Lishyk253502Calculator.View;

public partial class CalculatesPage : ContentPage
{
    public CalculatesPage()
    {
        InitializeComponent();
    }
    private string currentInput = string.Empty;
    private double result = 0.0;
    private char currentOperator = '0';
    private double MemoryValue = 0.0;
    private bool flagMRC = false;
    private bool MemoryUse = false;

    void OnPercentage(object sender, EventArgs e)
    {
        if (double.TryParse(currentInput, out double inputNumber))
        {
            double percentage = inputNumber / 100.0;
            currentInput = percentage.ToString();
            UpdateDisplay();
        }
    }

    void OnModule(object sender, EventArgs e)
    {
        if (double.TryParse(currentInput, out double inputNumber))//out это параметр, в который будет записан результат преобразования
        {
            double result = Math.Abs(inputNumber);
            currentInput = result.ToString();
            UpdateDisplay();
        }
    }


    void OnClear(object sender, EventArgs e)
    {
        currentInput = string.Empty;
        result = 0.0;
        currentOperator = '0';
        //UpdateDisplay();
        Result.Text = "0";
    }

    void OnBack(object sender, EventArgs e)
    {
        if (currentInput.Length > 0)
        {
            currentInput = currentInput.Substring(0, currentInput.Length - 1);
            UpdateDisplay();
            if (string.IsNullOrEmpty(currentInput))
            {
                Result.Text = "0";
            }
        }
    }

    void OnFraction(object sender, EventArgs e)
    {
        if (double.TryParse(currentInput, out double inputNumber))
        {
            if (inputNumber != 0)
            {
                double fractionResult = 1 / inputNumber;
                currentInput = fractionResult.ToString();
                UpdateDisplay();
            }
        }
    }

    void OnDegree(object sender, EventArgs e)
    {
        if (double.TryParse(currentInput, out double inputNumber))
        {
            double degreeResult = Math.Pow(inputNumber, 2);
            currentInput = degreeResult.ToString();
            UpdateDisplay();
        }
    }

    void OnSqrt(object sender, EventArgs e)
    {
        if (double.TryParse(currentInput, out double inputNumber))
        {
            double sqrtResult = Math.Sqrt(inputNumber);
            currentInput = sqrtResult.ToString();
            UpdateDisplay();
        }
    }

    void OnSelectDiv(object sender, EventArgs e)//обработчик события
    {
        ApplyOperator('/');
    }
    void OnSelectMult(object sender, EventArgs e)
    {
        ApplyOperator('*');
    }
    void OnSelectSub(object sender, EventArgs e)
    {
        ApplyOperator('-');
    }
    void OnSelectSum(object sender, EventArgs e)
    {
        ApplyOperator('+');
    }
    void ApplyOperator(char operatorSymbol)//принимает символ оператора в качестве параметра и выполняет операцию над текущим результатом и введенным числом.
    {
        if (double.TryParse(currentInput, out double inputNumber))
        {
            result = PerformCalculation(result, inputNumber, currentOperator);
            currentInput = string.Empty;
            currentOperator = operatorSymbol;
            UpdateDisplay();
        }
    }
    void OnSelectNumber(object sender, EventArgs e) //объект кот вызвал событие и аргумены
    {
        Button numberButton = (Button)sender; //приводим sender к типу Button
        currentInput += numberButton.Text; //+=добавления текста числа в конец строки.
        UpdateDisplay();
    }

    void OnNegative(object sender, EventArgs e)
    {
        if (double.TryParse(currentInput, out double inputNumber))
        {
            inputNumber *= -1;
            currentInput = inputNumber.ToString();
            UpdateDisplay();
        }
    }

    void OnCalculate(object sender, EventArgs e)
    {
        if (double.TryParse(currentInput, out double inputNumber))
        {
            result = PerformCalculation(result, inputNumber, currentOperator);
            currentInput = result.ToString();
            UpdateDisplay();
            currentOperator = '0'; 
        }
    }

    void UpdateDisplay()
    {
         Result.Text = currentInput;
    }
    double PerformCalculation(double operand1, double operand2, char operatorSymbol)
    {
        switch (operatorSymbol)
        {
            case '+':
                return operand1 + operand2;
            case '-':
                return operand1 - operand2;
            case '*':
                return operand1 * operand2;
            case '/':
                return operand1 / operand2;
            default:
                return operand2; // If no valid operator, return the second operand
        }
    }

    // Memory Clear (MC)
    void OnMC(object sender, EventArgs e)
    {
        if (MemoryUse)
        {
            OnMRButton.IsEnabled = false;
            OnMRButton.BackgroundColor = Color.FromArgb("#2e2d2d");
            OnMСButton.IsEnabled = false;
            OnMСButton.BackgroundColor = Color.FromArgb("#2e2d2d");
            OnMRCButton.IsEnabled = false;
            OnMRCButton.BackgroundColor = Color.FromArgb("#2e2d2d");
            MemoryValue = 0.0;
            MemoryUse = false; 
        }
    }
    
    // Memory Read (MR)
    void OnMR(object sender, EventArgs e)
    {
        if (MemoryUse)
        {
            currentInput = MemoryValue.ToString();
            result = MemoryValue;
            UpdateDisplay();
        }
    }

    // Memory Add (M+)
    void OnMPlus(object sender, EventArgs e)
    {
        if (double.TryParse(currentInput, out double inputNumber))
        {
            OnMRButton.IsEnabled = true;
            OnMRButton.BackgroundColor = Color.FromArgb("#696969");
            OnMСButton.IsEnabled = true;
            OnMСButton.BackgroundColor = Color.FromArgb("#696969");
            OnMRCButton.IsEnabled = true;
            OnMRCButton.BackgroundColor = Color.FromArgb("#696969");
            OnCalculate(sender, e);
            MemoryValue += inputNumber;
            MemoryUse = true;
        }
    }

    // Memory Subtract (M-)
    void OnMMin(object sender, EventArgs e)
    {
        if (double.TryParse(currentInput, out double inputNumber))
        {
            OnMRButton.IsEnabled = true;
            OnMRButton.BackgroundColor = Color.FromArgb("#696969");
            OnMСButton.IsEnabled = true;
            OnMСButton.BackgroundColor = Color.FromArgb("#696969");
            OnMRCButton.IsEnabled = true;
            OnMRCButton.BackgroundColor = Color.FromArgb("#696969");
            OnCalculate(sender, e);
            MemoryValue -= inputNumber;
            MemoryUse = true; 
        }
    }

    // Memory Save (MS)
    void OnMS(object sender, EventArgs e)
    {
        if (double.TryParse(currentInput, out double inputNumber))
        {
            OnMRButton.IsEnabled = true;
            OnMRButton.BackgroundColor = Color.FromArgb("#696969");
            OnMСButton.IsEnabled = true;
            OnMСButton.BackgroundColor = Color.FromArgb("#696969");
            OnMRCButton.IsEnabled = true;
            OnMRCButton.BackgroundColor = Color.FromArgb("#696969");
            OnCalculate(sender, e);
            MemoryValue = inputNumber;
            MemoryUse = true;
        }
    }

    //Memory Recall (MRC)
    void OnMRC(object sender, EventArgs e)
    {
        if (MemoryUse)
        {
            if (!flagMRC)
            {
                OnMR(sender, e);
                flagMRC = true;
            }
            else
            {
                OnMC(sender, e);
                flagMRC = false;
            }
        }
    }

}