﻿using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Shopich.Business_logic;
using Shopich.Models;
using Shopich.Repositories.interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Shopich.Controllers.api
{
    [ApiController]
    [Route("api/v1/orders")]
    [Authorize(AuthenticationSchemes = JwtBearerDefaults.AuthenticationScheme)]
    public class OrderController : Controller
    {
        private readonly IOrder _orderRepository;
        private readonly IOrders _ordersRepository;
        private readonly IUser _userRepository;

        public OrderController(IOrder orderRepository, IOrders ordersRepository, IUser userRepository)
        {
            _orderRepository = orderRepository;
            _ordersRepository = ordersRepository;
            _userRepository = userRepository;
        }

        /// <summary>
        /// Get list of orders
        /// </summary>
        /// <returns>List of orders</returns>
        /// <response code="200"></response>
        [HttpGet]
        public async Task<IEnumerable<Order>> GetAll()
        {
            var currentUser = await _userRepository.GetByEmail(User.Identity.Name);
            var orders = await _orderRepository.GetAllAcceptedForUser(currentUser.UserId);

            return orders;
        }

        /// <summary>
        /// Get order by id
        /// </summary>
        /// <param name="orderId"></param>
        /// <returns>Order object</returns>
        /// <response code="200"></response>
        [HttpGet("{orderId:int}")]
        public async Task<IActionResult> GetOrder(int orderId)
        {
            var order = await _orderRepository.GetById(orderId);
            var currentUser = await _userRepository.GetByEmail(User.Identity.Name);

            if (order == null)
            {
                return BadRequest("No such order");
            }
            else if (order.UserId != currentUser.UserId)
            {
                return BadRequest("Try to get another user's order");
            }
            else
            {
                return Json(order);
            }
        }

        /// <summary>
        /// Create order
        /// </summary>
        /// <returns>Approved order</returns>
        /// <response code="201"></response>
        [HttpPost]
        public async Task<IActionResult> CreateOrder()
        {
            var order = await _orderRepository.GetUnacceptedOrder((await _userRepository.GetByEmail(User.Identity.Name)).UserId);

            order = OrderLogic.ApproveOrder(order);

            _orderRepository.Update(order);
            await _orderRepository.Save();

            return CreatedAtAction("order", order);
        }


        /// <summary>
        /// Delete order
        /// </summary>
        /// <param name="orderId"></param>
        /// <returns>Status code</returns>
        /// <response code="204"></response>
        /// <response code="400"></response>
        [HttpDelete("{orderId}")]
        public async Task<IActionResult> DeleteOrder(int orderId)
        {
            var order = await _orderRepository.GetById(orderId);
            var currentUser = await _userRepository.GetByEmail(User.Identity.Name);

            if (order == null)
            {
                return BadRequest("No such order");
            }
            else if (order.UserId != currentUser.UserId)
            {
                return BadRequest("Try to delete another user's order");
            }
            else
            {
                await _orderRepository.Delete(orderId);
                await _orderRepository.Save();
            }

            return NoContent();
        }
    }
}
