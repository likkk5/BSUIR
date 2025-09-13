using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using _253502LishykK.Persistence.Data;
using Microsoft.EntityFrameworkCore;

namespace _253502LishykK.Persistence.Repository
{
    public class EfRepository<T> : IRepository<T> where T : Entity
    {
        protected readonly AppDbContext _context;
        protected readonly DbSet<T> _entities;

        public EfRepository(AppDbContext context)
        {
            _context = context;
            _entities = context.Set<T>();
        }

        public async Task<T> GetByIdAsync(int id, CancellationToken cancellationToken = default, params Expression<Func<T, object>>[] includesProperties)
        {
            var query = _entities.AsQueryable();
            if (includesProperties.Any())
            {
                foreach (var included in includesProperties)
                {
                    query = query.Include(included);
                }
            }
            return await query.FirstOrDefaultAsync(e => e.Id == id, cancellationToken);
        }

        public async Task<IReadOnlyList<T>> ListAllAsync(CancellationToken cancellationToken = default)
        {
            return await _entities.ToListAsync(cancellationToken);
        }

        public async Task<IReadOnlyList<T>> ListAsync(Expression<Func<T, bool>> filter, CancellationToken cancellationToken = default, params Expression<Func<T, object>>[] includesProperties)
        {
            var query = _entities.AsQueryable();
            if (includesProperties.Any())
            {
                foreach (var included in includesProperties)
                {
                    query = query.Include(included);
                }
            }
            return await query.Where(filter).ToListAsync(cancellationToken);
        }

        public async Task AddAsync(T entity, CancellationToken cancellationToken = default)
        {
            await _entities.AddAsync(entity, cancellationToken);
            await _context.SaveChangesAsync(cancellationToken);
        }

        public async Task UpdateAsync(T entity, CancellationToken cancellationToken = default)
        {
            _context.Entry(entity).State = EntityState.Modified;
            await _context.SaveChangesAsync(cancellationToken);
        }

        public async Task DeleteAsync(T entity, CancellationToken cancellationToken = default)
        {
            _entities.Remove(entity);
            await _context.SaveChangesAsync(cancellationToken);
        }

        public async Task<T> FirstOrDefaultAsync(Expression<Func<T, bool>> filter, CancellationToken cancellationToken = default)
        {
            return await _entities.FirstOrDefaultAsync(filter, cancellationToken);
        }
        //public async Task<IEnumerable<T>> GetNominationWithParticipantsAsync(string nominationId, CancellationToken cancellationToken)
        //{
        //    // Предположим, что у вас есть метод, который возвращает номинации с участниками из контекста базы данных
        //    return (IEnumerable<T>)await _context.Nominations
        //        .Include(n => n.Participants)
        //        .Where(n => n.Id.Equals(nominationId))
        //        .ToListAsync(cancellationToken);
        //}

        public async Task<IEnumerable<Participant>> GetParticipantsByNominationAsync(string nominationId, CancellationToken cancellationToken)
        {
            var namId = int.Parse(nominationId);
            return await _context.Participants
                .Where(p => p.NominationId.Equals(namId))
                .ToListAsync(cancellationToken);
        }

        async Task<IEnumerable<Nomination>> IRepository<T>.GetAllAsync(CancellationToken cancellationToken)
        {
            return await _context.Set<Nomination>().ToListAsync(cancellationToken);
        }
    }
}
