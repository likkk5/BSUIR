using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;

namespace _253502LishykK.Persistence.Repository
{
    public class FakeNominationRepository : IRepository<Nomination>
    {
        private readonly List<Nomination> _nominations;

        public FakeNominationRepository()
        {
            _nominations = new List<Nomination>
            {
                new Nomination("Народный танец",1),
                new Nomination("Классический танец", 2),
                new Nomination("Современный танец", 3),
                new Nomination("Бальный танец", 4),
                new Nomination("Эстрадный танец", 5),
                new Nomination("Уличный танец", 6),
            };
        }

        public async Task<Nomination> GetByIdAsync(int id, CancellationToken cancellationToken = default, params Expression<Func<Nomination, object>>[] includesProperties)
        {
            var query = _nominations.AsQueryable();
            if (includesProperties.Any())
            {
                foreach (var included in includesProperties)
                {
                    query = query.Include(included);
                }
            }
            return await query.FirstOrDefaultAsync(n => n.Id == id, cancellationToken);
        }

        public async Task<IReadOnlyList<Nomination>> ListAllAsync(CancellationToken cancellationToken = default)
        {
            return await Task.Run(() => _nominations.AsReadOnly(), cancellationToken);
        }

        public async Task<IReadOnlyList<Nomination>> ListAsync(Expression<Func<Nomination, bool>> filter, CancellationToken cancellationToken = default, params Expression<Func<Nomination, object>>[] includesProperties)
        {
            var query = _nominations.AsQueryable();
            if (includesProperties.Any())
            {
                foreach (var included in includesProperties)
                {
                    query = query.Include(included);
                }
            }
            return await query.Where(filter).ToListAsync(cancellationToken);
        }

        public async Task AddAsync(Nomination entity, CancellationToken cancellationToken = default)
        {
            _nominations.Add(entity);
            await Task.CompletedTask;
        }

        public async Task UpdateAsync(Nomination entity, CancellationToken cancellationToken = default)
        {
            var existingNomination = _nominations.FirstOrDefault(n => n.Id == entity.Id);
            if (existingNomination != null)
            {
                // Обновляем свойства существующей номинации
                existingNomination.Name = entity.Name;

            }
            await Task.CompletedTask;
        }

        public async Task DeleteAsync(Nomination entity, CancellationToken cancellationToken = default)
        {
            _nominations.Remove(entity);
            await Task.CompletedTask;
        }

        public async Task<Nomination> FirstOrDefaultAsync(Expression<Func<Nomination, bool>> filter, CancellationToken cancellationToken = default)
        {
            return await _nominations.AsQueryable().FirstOrDefaultAsync(filter, cancellationToken);
        }

        public async Task<IEnumerable<Participant>> GetParticipantsByNominationAsync(string nominationId, CancellationToken cancellationToken)
        {
            // Возвращаем участников номинации по идентификатору номинации
            var nomination = _nominations.FirstOrDefault(n => n.Id.Equals(nominationId));
            if (nomination != null)
            {
                return await Task.FromResult(nomination.Participants);
            }
            else
            {
                return Enumerable.Empty<Participant>();
            }
            // Предположим, что участников нет
            //return await Task.FromResult<IEnumerable<Participant>>(new List<Participant>());
        }
        public async Task<IEnumerable<Nomination>> GetAllAsync(CancellationToken cancellationToken)
        {
            return await Task.FromResult(_nominations);
        }
    }
}
