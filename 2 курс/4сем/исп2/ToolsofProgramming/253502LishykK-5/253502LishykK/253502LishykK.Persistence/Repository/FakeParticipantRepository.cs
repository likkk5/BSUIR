using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace _253502LishykK.Persistence.Repository
{
    public class FakeParticipantRepository : IRepository<Participant>
    {
        private readonly List<Participant> _participants;

        public FakeParticipantRepository()
        {
            _participants = new List<Participant>
            {
                new("Джэйн Доу", 100, "начинающие", "1:38", 1, 1),
                new("Варвара Комарова", 75, "начинающие", "1:30", 1, 2),
                new("Джэйн Смит", 90, "начинающие", "1:20", 2, 3),
                new("Виктория Титова", 89, "начинающие", "1:15", 2, 4),
                new("Рэйчел Кинг", 55, "средний уровень", "1:45", 3, 5),
                new("Ангелина Новикова", 85, "средний уровень", "1:37", 3, 6),
                new("Сюзанна Мартин", 37, "средний уровень", "2:00", 4, 7),
                new("Ева Максимова", 59, "средний уровень", "2:01", 4, 8),
                new("Джэйк Мерфи", 72, "продолжающие", "1:56", 5, 9),
                new("Валерия Кузнецова", 77, "продолжающие", "1:55", 5, 10),
                new("Лаурен Кастильо", 67, "продолжающие", "1:39", 6, 11),
                new("Стефания Захарова", 63, "продолжающие", "1:35", 6, 12),
            };
        }

        public async Task<Participant> GetByIdAsync(int id, CancellationToken cancellationToken = default, params Expression<Func<Participant, object>>[] includesProperties)
        {
            var query = _participants.AsQueryable();
            if (includesProperties.Any())
            {
                foreach (var included in includesProperties)
                {
                    query = query.Include(included);
                }
            }
            return await query.FirstOrDefaultAsync(p => p.Id == id, cancellationToken);
        }

        public async Task<IReadOnlyList<Participant>> ListAllAsync(CancellationToken cancellationToken = default)
        {
            return await Task.Run(() => _participants.AsReadOnly(), cancellationToken);
        }

        public async Task<IReadOnlyList<Participant>> ListAsync(Expression<Func<Participant, bool>> filter, CancellationToken cancellationToken = default, params Expression<Func<Participant, object>>[] includesProperties)
        {
            var query = _participants.AsQueryable();
            if (includesProperties.Any())
            {
                foreach (var included in includesProperties)
                {
                    query = query.Include(included);
                }
            }
            return await query.Where(filter).ToListAsync(cancellationToken);
        }

        public async Task AddAsync(Participant entity, CancellationToken cancellationToken = default)
        {
            _participants.Add(entity);
            await Task.CompletedTask;
        }

        public async Task UpdateAsync(Participant entity, CancellationToken cancellationToken = default)
        {
            var existingParticipant = _participants.FirstOrDefault(p => p.Id == entity.Id);
            if (existingParticipant != null)
            {
                // Обновляем свойства существующего участника
                existingParticipant.Name = entity.Name;
                existingParticipant.MandatoryProperty = entity.MandatoryProperty;
                existingParticipant.AdditionalProperty1 = entity.AdditionalProperty1;
                existingParticipant.AdditionalProperty2 = entity.AdditionalProperty2;
                existingParticipant.NominationId = entity.NominationId;
            }
            await Task.CompletedTask;
        }

        public async Task DeleteAsync(Participant entity, CancellationToken cancellationToken = default)
        {
            _participants.Remove(entity);
            await Task.CompletedTask;
        }

        public async Task<Participant> FirstOrDefaultAsync(Expression<Func<Participant, bool>> filter, CancellationToken cancellationToken = default)
        {
            return await _participants.AsQueryable().FirstOrDefaultAsync(filter, cancellationToken);
        }
        public async Task<IEnumerable<Participant>> GetParticipantsByNominationAsync(string nominationId, CancellationToken cancellationToken)
        {
            //var list = _participants.Where(p => p.NominationId.Equals(nominationId)).ToList();
            //return await Task.FromResult(list);
            //// Возвращаем участников по идентификатору номинации (предположительно, связь участника с номинацией)

            var namId = int.Parse(nominationId);
            return await Task.FromResult(_participants.Where(p => p.NominationId.Equals(namId)).ToList());
        }

        public Task<IEnumerable<Nomination>> GetAllAsync(CancellationToken cancellationToken)
        {
            throw new NotImplementedException();
        }

        //public async Task<IEnumerable<Participant>> GetAllAsync(CancellationToken cancellationToken)
        //{
        //    // Возвращаем всех участников
        //    return await Task.FromResult(_participants.ToList());
        //}
    }
}
