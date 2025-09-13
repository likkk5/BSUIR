using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _253502LishykK.Persistence.Repository;
using Microsoft.Extensions.DependencyInjection;

namespace _253502LishykK.Application
{
        public static class DbInitializer
        {
            public static async Task Initialize(IServiceProvider services)
            {
                // Получаем IUnitOfWork из IServiceProvider
                var unitOfWork = services.GetRequiredService<IUnitOfWork>();

                // Удаление и создание базы данных
                await unitOfWork.DeleteDataBaseAsync();
                await unitOfWork.CreateDataBaseAsync();

                // Добавление номинаций
                await unitOfWork.NominationRepository.AddAsync(new Nomination("Народный танец", 1));
                await unitOfWork.NominationRepository.AddAsync(new Nomination("Классический танец", 2));
                await unitOfWork.NominationRepository.AddAsync(new Nomination("Современный танец", 3));
                await unitOfWork.NominationRepository.AddAsync(new Nomination("Бальный танец", 4));
                await unitOfWork.NominationRepository.AddAsync(new Nomination("Эстрадный танец", 5));
                await unitOfWork.NominationRepository.AddAsync(new Nomination("Уличный танец", 6));
                await unitOfWork.SaveAllAsync();

                // Добавление участников
                //var participantRepository = new FakeParticipantRepository();
                //var nomination1 = await nominationRepository.GetByIdAsync(1);
                //var nomination2 = await nominationRepository.GetByIdAsync(2);
                //var nomination3 = await nominationRepository.GetByIdAsync(3);
                //var nomination4 = await nominationRepository.GetByIdAsync(4);
                //var nomination5 = await nominationRepository.GetByIdAsync(5);
                //var nomination6 = await nominationRepository.GetByIdAsync(6);

                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Джэйн Доу", 100, "начинающие", "1:38", 1, 1));
                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Варвара Комарова", 75, "начинающие", "1:30", 1, 2));
                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Джэйн Смит", 90, "начинающие", "1:20", 2, 3));
                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Виктория Титова", 89, "начинающие", "1:15", 2, 4));
                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Рэйчел Кинг", 55, "средний уровень", "1:45", 3, 5));
                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Ангелина Новикова", 85, "средний уровень", "1:37", 3, 6));
                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Сюзанна Мартин", 37, "средний уровень", "2:00", 4, 7));
                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Ева Максимова", 59, "средний уровень", "2:01", 4, 8));
                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Джэйк Мерфи", 72, "продолжающие", "1:56", 5, 9));
                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Валерия Кузнецова", 77, "продолжающие", "1:55", 5, 10));
                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Лаурен Кастильо", 67, "продолжающие", "1:39", 6, 11));
                await unitOfWork.ParticipantRepository.AddAsync(new Participant("Стефания Захарова", 63, "продолжающие", "1:35", 6, 12));
                await unitOfWork.SaveAllAsync();
            }
        }
}
