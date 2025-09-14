// See https://aka.ms/new-console-template for more information
using BAHDANAU_153502_Lab5.Entities;

Bank a = new Bank("Bank");
a.AddClient("Alex");
a.AddTarrif("vip", 10);
a.AddTarrif("premium", 20);
a.AddDeposit(100, "vip", "Alex");
a.AddClient("Oleg");
a.AddDeposit(10, "premium", "Oleg");

var res1 = a.GetTarrifsSortedByPercent();
Console.WriteLine("Tarrifs");
foreach (var item in res1)
{
    Console.WriteLine(item);
}

var res2 = a.GetSumPercents();
Console.WriteLine($"Sum percents {res2}");

var res3 = a.GetSumDeposits();
Console.WriteLine($"Sum deposits {res3}");

var res4 = a.GetClientNameWithMaxPercent();
Console.WriteLine($"Client name with max percent {res4}");

var res5 = a.GetClientCountGreaterSum(50);
Console.WriteLine($"Count is {res5}");

var res6 = a.GetSumListByClient();
Console.WriteLine("Sum list by client");
foreach (var item in res6)
{
    Console.WriteLine($"{item.Value}-{item.Key}");
}