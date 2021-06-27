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
    public class ProgressesController : Controller
    {
        private readonly IProgress _db;

        public ProgressesController(IProgress context)
        {
            _db = context;
        }

        [Authorize(Roles = "Admin")]
        // GET: Progresses
        public async Task<IActionResult> Index()
        {
            return View(_db.GetAll().ToList());
        }

        // GET: Progresses/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var progress = _db.GetAll().FirstOrDefault(m => m.Id == id);
            if (progress == null)
            {
                return NotFound();
            }

            return View(progress);
        }

        // GET: Progresses/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: Progresses/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,TotalCountTasks,CompletedTasks")] Progress progress)
        {
            if (ModelState.IsValid)
            {
                _db.Create(progress);
                _db.Save();
                return RedirectToAction(nameof(Index));
            }
            return View(progress);
        }

        // GET: Progresses/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var progress = _db.GetElement(id.GetValueOrDefault());
            if (progress == null)
            {
                return NotFound();
            }
            return View(progress);
        }

        // POST: Progresses/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,TotalCountTasks,CompletedTasks")] Progress progress)
        {
            if (id != progress.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _db.Update(progress);
                    _db.Save();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!ProgressExists(progress.Id))
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
            return View(progress);
        }

        // GET: Progresses/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var progress = _db.GetAll().FirstOrDefault(m => m.Id == id);
            if (progress == null)
            {
                return NotFound();
            }

            return View(progress);
        }

        // POST: Progresses/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            _db.Delete(id);
            _db.Save();
            return RedirectToAction(nameof(Index));
        }

        private bool ProgressExists(int id)
        {
            return _db.Exists(id);
        }
    }
}
