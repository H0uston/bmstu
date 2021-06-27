using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using DistanceLearning;
using DistanceLearning.Repositories.interfaces;
using Microsoft.AspNetCore.Authorization;

namespace DistanceLearning.Controllers
{
    public class RequestListsController : Controller
    {
        private readonly IRequestList _db;

        public RequestListsController(IRequestList context)
        {
            _db = context;
        }

        [Authorize(Roles = "Admin")]
        // GET: RequestLists
        public async Task<IActionResult> Index()
        {
            var distanceLearningDBContext = _db.Include(r => r.Group).Include(r => r.User);
            return View(await distanceLearningDBContext.ToListAsync());
        }

        public async Task<IActionResult> CreateRequest(int userId, int groupId)
        {
            try
            {
                var requestList = new RequestList();
                requestList.UserId = userId;
                requestList.GroupId = groupId;
                requestList.IsAwaiting = true;
                requestList.IsAccepted = false;
                requestList.IsDenied = false;
                _db.Create(requestList);
                _db.Save();

                return RedirectToRoute(new { controller = "Home", action = "Index"});
            }
            catch
            {
                throw new ArgumentException();
            }
        }

        // GET: RequestLists/Details/5
        public async Task<IActionResult> Details(int userId, int groupId)
        {
            if (userId == null || groupId == null)
            {
                return NotFound();
            }

            var requestList = await _db
                .Include(r => r.Group)
                .Include(r => r.User)
                .FirstOrDefaultAsync(m => m.UserId == userId && m.GroupId == groupId);
            if (requestList == null)
            {
                return NotFound();
            }

            return View(requestList);
        }

        // GET: RequestLists/Create
        public IActionResult Create()
        {
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name");
            ViewData["UserId"] = new SelectList(_db.GetUserDescriptions(), "Id", "Email");
            return View();
        }

        // POST: RequestLists/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("UserId,GroupId,IsAwaiting,IsAccepting,IsDenied")] RequestList requestList)
        {
            if (ModelState.IsValid)
            {
                _db.Create(requestList);
                _db.Save();
                return RedirectToAction(nameof(Index));
            }
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name", requestList.GroupId);
            ViewData["UserId"] = new SelectList(_db.GetUserDescriptions(), "Id", "Email", requestList.UserId);
            return View(requestList);
        }

        // GET: RequestLists/Edit/5
        public async Task<IActionResult> Edit(int userId, int groupId)
        {
            if (userId == null || groupId == null)
            {
                return NotFound();
            }

            var requestList = _db.GetElement(userId, groupId);
            if (requestList == null)
            {
                return NotFound();
            }
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name", requestList.GroupId);
            ViewData["UserId"] = new SelectList(_db.GetUserDescriptions(), "Id", "Email", requestList.UserId);
            return View(requestList);
        }

        // POST: RequestLists/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int userId, int groupId, [Bind("UserId,GroupId,IsAwaiting,IsAccepted,IsDenied")] RequestList requestList)
        {
            if (userId != requestList.UserId || groupId != requestList.GroupId)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _db.Update(requestList);
                    _db.Save();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!RequestListExists(requestList.UserId, requestList.GroupId))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name", requestList.GroupId);
            ViewData["UserId"] = new SelectList(_db.GetUserDescriptions(), "Id", "Email", requestList.UserId);
            return View(requestList);
        }

        // GET: RequestLists/Delete/5
        public async Task<IActionResult> Delete(int userId, int groupId)
        {
            if (userId == null || groupId == null)
            {
                return NotFound();
            }

            var requestList = await _db
                .Include(r => r.Group)
                .Include(r => r.User)
                .FirstOrDefaultAsync(m => m.UserId == userId && m.GroupId == groupId);
            if (requestList == null)
            {
                return NotFound();
            }

            return View(requestList);
        }

        // POST: RequestLists/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int userId, int groupId)
        {
            _db.Delete(userId, groupId);
            _db.Save();
            return RedirectToAction(nameof(Index));
        }

        private bool RequestListExists(int userId, int groupId)
        {
            return _db.Exists(userId, groupId);
        }
    }
}
