using BAHDANAU_153502_Lab5.Entities;
using BAHDANAU_153502_Lab5.Collections;
using BAHDANAU_153502_Lab5.Exceptions;

/*Bank alphabank = new("Alpha-Bank");
Client alex = new Client("Alexander");
Deposit d1 = new Deposit(100, 15);
Deposit d2 = new Deposit(500, 5);
alphabank.AddClient(alex);
alex.AddDeposit(d1);
alex.AddDeposit(d2);
Client oleg = new Client("Oleg");
alphabank.AddClient(oleg);
oleg.AddDeposit(new Deposit(10000, 1));
Console.WriteLine($"Payout amount is {alphabank.PayoutAmount}");
d1.IncreaseDeposit(1000);
Console.WriteLine("Alex's deposit increased by 1000");
Console.WriteLine($"Payout amount is {alphabank.PayoutAmount}");*/

Bank bank = new("Bank");
Journal journal = new();
bank.AddClientEvent += journal.Log;
Client oleg = new Client("oleg");
bank.AddClient(oleg);
oleg.AddDepositEvent += journal.Log;

oleg.AddDeposit(new Deposit(1000, 10));
oleg.AddDeposit(new Deposit(100, 1));

Console.WriteLine("Logs are");
Console.WriteLine(journal.GetLogs());

oleg.AddDepositEvent += (string message) => Console.WriteLine($"Console log: {message}");

oleg.AddDeposit(new Deposit(100, 1));

MyCustomCollection<int> collection = new MyCustomCollection<int>();

collection.Add(1);
collection.Add(2);
collection.Add(3); 
collection.Add(4);

Console.WriteLine("Foreach items");
foreach (var item in collection)
{
    Console.Write(item);
}
Console.WriteLine();

try
{
    collection.Remove(10);
}
catch (ObjectNotFoundException ex)
{
    Console.WriteLine(ex.Message);
}

try
{
    int v = collection[10];
}
catch (IndexOutOfRangeException ex)
{
    Console.WriteLine(ex.Message);
}