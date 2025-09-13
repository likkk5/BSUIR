using BAHDANAU_153502_Lab5.Entities;

Bank alphabank = new("Alpha-Bank");
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
Console.WriteLine($"Payout amount is {alphabank.PayoutAmount}");
