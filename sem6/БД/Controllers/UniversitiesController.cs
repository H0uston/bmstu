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
    public class UniversitiesController : Controller
    {
        private readonly IUniversity _db;

        public UniversitiesController(IUniversity context)
        {
            _db = context;
        }

        [Authorize(Roles = "Admin")]
        // GET: Universities
        public async Task<IActionResult> Index()
        {
            return View(_db.GetAll().ToList());
        }

        // GET: Universities/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var university = _db.GetAll().FirstOrDefault(m => m.Id == id);
            if (university == null)
            {
                return NotFound();
            }

            return View(university);
        }

        // GET: Universities/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: Universities/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,Name")] University university)
        {
            if (ModelState.IsValid)
            {
                _db.Create(university);
                _db.Save();
                return RedirectToAction(nameof(Index));
            }
            return View(university);
        }

        // GET: Universities/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var university = _db.GetElement(id.GetValueOrDefault());
            if (university == null)
            {
                return NotFound();
            }
            return View(university);
        }

        // POST: Universities/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Name")] University university)
        {
            if (id != university.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _db.Update(university);
                    _db.Save();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!UniversityExists(university.Id))
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
            return View(university);
        }

        // GET: Universities/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var university = _db.GetAll().FirstOrDefault(m => m.Id == id);
            if (university == null)
            {
                return NotFound();
            }

            return View(university);
        }

        // POST: Universities/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            _db.Delete(id);
            _db.Save();
            return RedirectToAction(nameof(Index));
        }

        private bool UniversityExists(int id)
        {
            return _db.Exists(id);
        }
    }
}
