using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using SQLite;
using Lishyk253502Calculator.Entities;
using Lishyk253502Calculator.Services;

namespace Lishyk253502Calculator.Service
{
    public class SQLiteService : IDbService
    {
        private readonly SQLiteConnection _database;

        public SQLiteService()
        {
            string dbPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "mydatabase.db");
            _database = new SQLiteConnection(dbPath);
            _database.CreateTable<SushiSetEntity>(); //созд таблицу бд
            _database.CreateTable<SushiEntity>();
            Init();
        }

        public void Init()
        {
            if (_database.Table<SushiSetEntity>().Any() || _database.Table<SushiEntity>().Any())
            {
                return;
            }

            // Создаем несколько наборов суши и добавляем их в базу данных
            var sushiSet1 = new SushiSetEntity { Name = "Set 1(example)" };
            _database.Insert(sushiSet1);

            // Создаем несколько видов суши и добавляем их в базу данных, привязывая к соответствующим наборам
            var sushi1 = new SushiEntity { Name = "Sushi A", SushiSetId = sushiSet1.Id };
            var sushi2 = new SushiEntity { Name = "Sushi B", SushiSetId = sushiSet1.Id };
            var sushi3 = new SushiEntity { Name = "Sushi C", SushiSetId = sushiSet1.Id };
            var sushi4 = new SushiEntity { Name = "Sushi D", SushiSetId = sushiSet1.Id };
            var sushi5 = new SushiEntity { Name = "Sushi E", SushiSetId = sushiSet1.Id };

            _database.Insert(sushi1);
            _database.Insert(sushi2);
            _database.Insert(sushi3);
            _database.Insert(sushi4);
            _database.Insert(sushi5);

            var sushiSetsData = new[]
            {
                new { Name = "Сет 2", Sushis = new[] { "Ролл с копченым лососем", "Ролл черный дракон", "Ролл с лососем и сыром", "Лосось Торо", "Лосось Гравлакс", "Лосось Эдо", "Лосось Абури" } },
                new { Name = "Сет Зеленый (Мидори)", Sushis = new[] { "Морковь", "Огурец", "Цукини", "Авокадо" } },
                new { Name = "Сет Белый (Широ)", Sushis = new[] { "Морской окунь", "Палтус Эдо", "Морской гребешок Эдо", "Макрель Эдо" } },
                new { Name = "Сет Красный (Ака)", Sushis = new[] { "Лосось Эдо", "Лосось Гравлакс", "Лосось Абури", "Тунец Эдо" } },
                new { Name = "Сет Вегетарианский", Sushis = new[] { "Ролл Вегас", "Хмини ролл с перцем", "Хмини ролл с маринованными водорослями", "Хмини ролл с авокадо", "Хмини ролл с огурцом" } },
                new { Name = "Сет 16 Нигири", Sushis = new[] { "Лосось Гравлакс", "Лосось Торо", "Макрель Эдо", "Тунец Татаки", "Лосось Эдо", "Авокадо", "Огурец", "Морской окунь" } }
            };

            foreach (var sushiSetData in sushiSetsData)
            {
                var sushiSet = new SushiSetEntity { Name = sushiSetData.Name };
                _database.Insert(sushiSet);

                foreach (var sushiName in sushiSetData.Sushis)
                {
                    var sushi = new SushiEntity { Name = sushiName, SushiSetId = sushiSet.Id };
                    _database.Insert(sushi);
                }
            }
            //InsertAll принимает коллекцию объектов и выполняет операцию вставки каждого отдельного элемента в таблицу базы данных
        }

        public IEnumerable<SushiSetEntity> GetAllSushiSets()
        {
            return _database.Table<SushiSetEntity>().ToList();
        }

        public IEnumerable<SushiEntity> GetSushisInSet(int sushiSetId)
        {
            return _database.Table<SushiEntity>().Where(sushi => sushi.SushiSetId == sushiSetId).ToList();
            //Table<T>().Where() получить отфильтрованные данные из таблицы БД 
        }
        public void ClearDatabase()
        {
            _database.DeleteAll<SushiSetEntity>();
            _database.DeleteAll<SushiEntity>();
        }
    }
}