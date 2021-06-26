﻿using Shopich.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;

namespace Shopich.Repositories.interfaces
{
    public interface IReview
    {
        public Task<Review[]> GetAll();
        public Task<Review[]> GetAllByProductId(int productId);
        public Task Create(Review entity);
        public Task<Review> GetById(int id);
        public Task<Review> GetByProductIdAndUserId(int productId, int userId);
        public void Update(Review entity);
        public Task<int?> Delete(int id);
        public Task Save();
        public IQueryable<Review> Include(params Expression<Func<Review, object>>[] includeProperties);
        public bool Exists(int id);
        public bool ExistsByUserId(int id);

        public bool ExistsByProductIdAndUserId(int productId, int userId);
    }
}