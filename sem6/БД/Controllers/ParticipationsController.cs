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
    public class ParticipationsController : Controller
    {
        private readonly IParticipation _db;

        public ParticipationsController(IParticipation context)
        {
            _db = context;
        }

        [Authorize(Roles = "Admin")]
        // GET: Participations
        public async Task<IActionResult> Index()
        {
            var distanceLearningDBContext = _db.Include(p => p.Group).Include(p => p.Progress).Include(p => p.RoleNavigation).Include(p => p.User);
            return View(await distanceLearningDBContext.ToListAsync());
        }

        // GET: Participations/Details/5
        public async Task<IActionResult> Details(int userId, int groupId)
        {
            if (userId == null || groupId == null)
            {
                return NotFound();
            }

            var participation = await _db
                .Include(p => p.Group)
                .Include(p => p.Progress)
                .Include(p => p.RoleNavigation)
                .Include(p => p.User)
                .FirstOrDefaultAsync(m => m.UserId == userId && m.GroupId == groupId);
            if (participation == null)
            {
                return NotFound();
            }

            return View(participation);
        }

        // GET: Participations/Create
        public IActionResult Create()
        {
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name");
            ViewData["ProgressId"] = new SelectList(_db.GetProgresses(), "Id", "Id");
            ViewData["Role"] = new SelectList(_db.GetRoles(), "Id", "Description");
            ViewData["UserId"] = new SelectList(_db.GetUserDescriptions(), "Id", "Email");
            return View();
        }

        // POST: Participations/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("UserId,Role,GroupId,ProgressId")] Participation participation)
        {
            if (ModelState.IsValid)
            {
                _db.Create(participation);
                _db.Save();
                return RedirectToAction(nameof(Index));
            }
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name", participation.GroupId);
            ViewData["ProgressId"] = new SelectList(_db.GetProgresses(), "Id", "Id", participation.ProgressId);
            ViewData["Role"] = new SelectList(_db.GetRoles(), "Id", "Description", participation.Role);
            ViewData["UserId"] = new SelectList(_db.GetUserDescriptions(), "Id", "Email", participation.UserId);
            return View(participation);
        }

        // GET: Participations/Edit/5
        public async Task<IActionResult> Edit(int userId, int groupId)
        {
            if (userId == null || groupId == null)
            {
                return NotFound();
            }

            var participation = _db.GetElement(userId, groupId);
            if (participation == null)
            {
                return NotFound();
            }
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name", participation.GroupId);
            ViewData["ProgressId"] = new SelectList(_db.GetProgresses(), "Id", "Id", participation.ProgressId);
            ViewData["Role"] = new SelectList(_db.GetRoles(), "Id", "Description", participation.Role);
            ViewData["UserId"] = new SelectList(_db.GetUserDescriptions(), "Id", "Email", participation.UserId);
            return View(participation);
        }

        // POST: Participations/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int userId, int groupId, [Bind("UserId,Role,GroupId,ProgressId")] Participation participation)
        {
            if (userId != participation.UserId || groupId != participation.GroupId)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _db.Update(participation);
                    _db.Save();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!ParticipationExists(participation.UserId, participation.GroupId))
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
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name", participation.GroupId);
            ViewData["ProgressId"] = new SelectList(_db.GetProgresses(), "Id", "Id", participation.ProgressId);
            ViewData["Role"] = new SelectList(_db.GetRoles(), "Id", "Description", participation.Role);
            ViewData["UserId"] = new SelectList(_db.GetUserDescriptions(), "Id", "Email", participation.UserId);
            return View(participation);
        }

        // GET: Participations/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var participation = _db
                .Include(p => p.Group)
                .Include(p => p.Progress)
                .Include(p => p.RoleNavigation)
                .Include(p => p.User)
                .FirstOrDefaultAsync(m => m.UserId == id);
            if (participation == null)
            {
                return NotFound();
            }

            return View(participation);
        }

        // POST: Participations/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int userId, int groupId)
        {
            _db.Delete(userId, groupId);
            _db.Save();
            return RedirectToAction(nameof(Index));
        }

        private bool ParticipationExists(int userId, int groupId)
        {
            return _db.Exists(userId, groupId);
        }
    }
}
