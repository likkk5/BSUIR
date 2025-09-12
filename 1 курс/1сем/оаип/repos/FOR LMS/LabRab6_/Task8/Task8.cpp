#include <iostream>
#include <string>

std::string CheckStrings(std::string s, std::string t, int len_s, int len_t)
{
	int j, pos, pred_pos, stop_pos, len_check;
	char ch;
		
	stop_pos = 0;
	pred_pos = 0;
	len_check = 0;

	// идем направо
	for (j = 0; j < len_t; j++)
	{
		pos = s.find(t[j], pred_pos);

		if (pos != std::string::npos)
		{
	    	pred_pos = pos + 1;
			len_check = len_check + 1;
			stop_pos = j;
		}
		else
		{
			stop_pos = stop_pos + 1;
			pred_pos = 1;
			break;
		}
	}
	
	if (len_check == len_t)
	{
		return "YES";
	}
	else
	{
		// идем налево
		// переворачиваем строку s 
		for (j = 0;j < len_s/2;j++)
		{
			ch = s[j];
			s[j] = s[len_s - 1 - j];
			s[len_s - 1 - j] = ch;
		}
	
		for (j = stop_pos; j < len_t; j++)
		{
			pos = s.find(t[j], pred_pos);

			if (pos != std::string::npos)
			{
				pred_pos = pos + 1;
				len_check = len_check + 1;
			}
			else
			{
				break;
			}
		}

		if (len_check == len_t)
		{
			return "YES";
		}
		else
		{
			return "NO";
		}
	}
}

int main()
{
	std::string ss, tt;
	int q, i, len_ss, len_tt, all_len = 0;
	std::cin >> q;
	if ((q >= 1) && (q <= 500))
	{
		for (i = 0;i < q;i++)
		{
			std::cin >> ss;
			len_ss = ss.length();
			all_len = all_len + len_ss;
			if ((len_ss >= 1) && (len_ss <= 500) && (all_len <= 500))
			{
				std::cin >> tt;
				len_tt = tt.length();
				if ((len_tt >= 1) && (len_tt <= 2 * len_ss - 1))
				{
					std::cout << CheckStrings (ss, tt, len_ss, len_tt) << "\n";
				}
			}
		}
	}
	return 0;
}

