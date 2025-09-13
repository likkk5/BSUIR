using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using Lishyk253502Calculator.Entities;

namespace Lishyk253502Calculator.Services
{
    public class RateService : IRateService
    {
        private readonly HttpClient _httpClient;

        public RateService()
        {
            _httpClient = new HttpClient(); //клиент HTTP для отправки запросов к внешнему API
        }

        public async Task<IEnumerable<Rate>> GetRates(DateTime date)
        {
            try
            {
                string apiUrl = $"https://www.nbrb.by/api/exrates/rates?ondate={date:yyyy-MM-dd}&periodicity=0"; //формирует URL для запроса к внешнему API на основе переданной даты

                HttpResponseMessage response = await _httpClient.GetAsync(apiUrl); //отправляет синхронный запрос к API

                if (response.IsSuccessStatusCode)
                {
                    string content = await response.Content.ReadAsStringAsync(); 
                    List<Rate> rates = JsonSerializer.Deserialize<List<Rate>>(content);
                    //считывает содержимое ответа и десериализует(байты->объект)его из JSON в объект типа List<Rate>
                    return rates;
                }
                else
                {
                    throw new HttpRequestException($"Failed to get rates. Status code: {response.StatusCode}");
                }
            }
            catch (Exception ex)
            {
                throw new Exception("Error while getting rates", ex);
            }
        }

        //    public IEnumerable<Rate> GetRates(DateTime date)
        //    {
        //        try
        //        {
        //            string apiUrl = $"https://www.nbrb.by/api/exrates/rates?ondate={date:yyyy-MM-dd}&periodicity=0"; //формирует URL для запроса к внешнему API на основе переданной даты

        //            HttpResponseMessage response = _httpClient.GetAsync(apiUrl).GetAwaiter().GetResult();//отправляет синхронный запрос к API

        //            if (response.IsSuccessStatusCode)
        //            {
        //                string content = response.Content.ReadAsStringAsync().GetAwaiter().GetResult();
        //                List<Rate> rates = JsonSerializer.Deserialize<List<Rate>>(content);
        //                //считывает содержимое ответа и десериализует его из JSON в объект типа List<Rate>
        //                return rates;
        //            }
        //            else
        //            {
        //                throw new HttpRequestException($"Failed to get rates. Status code: {response.StatusCode}");
        //            }
        //        }
        //        catch (Exception ex)
        //        {
        //            throw new Exception("Error while getting rates", ex);
        //        }
        //    }
        //}

    }

}