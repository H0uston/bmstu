﻿using Shopich.Repositories.interfaces;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Threading.Tasks;
using System.Collections;
using Shopich.Models;

namespace Shopich.Repositories.implementations
{
    public class PostgreSQLOrdersRepository : IOrders
    {
        private ShopichContext _dbContext;

        public PostgreSQLOrdersRepository(ShopichContext context)
        {
            this._dbContext = context;
        }

        public async Task<Orders[]> GetAll()
        {
            return await _dbContext.Orders.ToArrayAsync();
        }

        public async Task Create(Orders entity)
        {
            await _dbContext.Orders.AddAsync(entity);
        }

        public async Task<Orders> GetById(int id)
        {
            return await _dbContext.Orders.FirstOrDefaultAsync(o => o.OrdersId == id);
        }

        public async Task<Orders[]> GetProductsInCart(int orderId)
        {
            return await _dbContext.Orders.Where(o => o.OrderId == orderId).ToArrayAsync();
        }

        public void Update(Orders entity)
        {
            _dbContext.Update(entity);
        }

        public async Task<int?> Delete(int id)
        {
            if (this.Exists(id))
            {
                _dbContext.Orders.Remove(await this.GetById(id));

                return id;
            }

            return null;
        }

        public async Task Save()
        {
            await _dbContext.SaveChangesAsync();
        }

        public IQueryable<Orders> Include(params Expression<Func<Orders, object>>[] includeProperties)
        {
            IQueryable<Orders> query = _dbContext.Orders;
            return includeProperties.Aggregate(query, (current, includeProperty) => current.Include(includeProperty));
        }


        public bool Exists(int id)
        {
            return _dbContext.Orders.Find(id) != null;
        }
    }
}