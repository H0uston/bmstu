using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using DistanceLearning.Repositories;
using DistanceLearning.Repositories.interfaces;
using Microsoft.AspNetCore.Authorization;

namespace DistanceLearning.Controllers
{
    public class UserDescriptionsController : Controller
    {
        private readonly IUserDescription _db;

        public UserDescriptionsController(IUserDescription db)
        {
            _db = db;
        }

        [Authorize(Roles = "Admin")]
        // GET: UserDescriptions
        public async Task<IActionResult> Index()
        {
            var distanceLearningDBContext = _db.Include(u => u.UniversityNavigation);
            return View(distanceLearningDBContext.ToList());
        }

        // GET: UserDescriptions/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var userDescription = _db.Include(u => u.UniversityNavigation).FirstOrDefault(m => m.Id == id);
            if (userDescription == null)
            {
                return NotFound();
            }

            return View(userDescription);
        }

        // GET: UserDescriptions/Create
        public IActionResult Create()
        {
            ViewData["University"] = new SelectList(_db.GetUniversities(), "Id", "Name");
            return View();
        }

        // POST: UserDescriptions/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,Name,Email,Password,Birthday,University,Role")] UserDescription userDescription)
        {
            if (ModelState.IsValid)
            {
                _db.Create(userDescription);
                _db.Save();
                return RedirectToAction(nameof(Index));
            }
            ViewData["University"] = new SelectList(_db.GetUniversities(), "Id", "Name", userDescription.University);
            return View(userDescription);
        }

        // GET: UserDescriptions/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var userDescription = _db.GetElement(id.GetValueOrDefault());
            if (userDescription == null)
            {
                return NotFound();
            }
            ViewData["University"] = new SelectList(_db.GetUniversities(), "Id", "Name", userDescription.University);
            return View(userDescription);
        }

        // POST: UserDescriptions/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Name,Email,Password,Birthday,University,Role")] UserDescription userDescription)
        {
            if (id != userDescription.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _db.Update(userDescription);
                    _db.Save();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!UserDescriptionExists(userDescription.Id))
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
            ViewData["University"] = new SelectList(_db.GetUniversities(), "Id", "Name", userDescription.University);
            
            return View(userDescription);
        }

        // GET: UserDescriptions/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var userDescription = _db.Include(u => u.UniversityNavigation).FirstOrDefault(m => m.Id == id);
            if (userDescription == null)
            {
                return NotFound();
            }

            return View(userDescription);
        }

        // POST: UserDescriptions/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            _db.Delete(id);
            _db.Save();
            return RedirectToAction(nameof(Index));
        }

        private bool UserDescriptionExists(int id)
        {
            return _db.GetElement(id) != null;
        }
    }
}
