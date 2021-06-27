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
    public class FilesController : Controller
    {
        private readonly IFile _db;

        public FilesController(IFile context)
        {
            _db = context;
        }

        [Authorize(Roles = "Admin")]
        // GET: Files
        public async Task<IActionResult> Index()
        {
            var distanceLearningDBContext = _db.Include(f => f.Group).Include(f => f.OwnerNavigation);
            return View(await distanceLearningDBContext.ToListAsync());
        }

        // GET: Files/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var files = _db.Include(f => f.Group).Include(f => f.OwnerNavigation).FirstOrDefaultAsync(m => m.Id == id);
            if (files == null)
            {
                return NotFound();
            }

            return View(files);
        }

        // GET: Files/Create
        public IActionResult Create()
        {
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name");
            ViewData["Owner"] = new SelectList(_db.GetUserDescriptions(), "Id", "Email");
            return View();
        }

        // POST: Files/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,Name,Path,DateOfLoad,Owner,GroupId")] Files files)
        {
            if (ModelState.IsValid)
            {
                _db.Create(files);
                _db.Save();
                return RedirectToAction(nameof(Index));
            }
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name", files.GroupId);
            ViewData["Owner"] = new SelectList(_db.GetUserDescriptions(), "Id", "Email", files.Owner);
            return View(files);
        }

        // GET: Files/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var files = _db.GetElement(id.GetValueOrDefault());
            if (files == null)
            {
                return NotFound();
            }
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name", files.GroupId);
            ViewData["Owner"] = new SelectList(_db.GetUserDescriptions(), "Id", "Email", files.Owner);
            return View(files);
        }

        // POST: Files/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Name,Path,DateOfLoad,Owner,GroupId")] Files files)
        {
            if (id != files.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _db.Update(files);
                    _db.Save();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!FilesExists(files.Id))
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
            ViewData["GroupId"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Name", files.GroupId);
            ViewData["Owner"] = new SelectList(_db.GetGroupDescriptions(), "Id", "Email", files.Owner);
            return View(files);
        }

        // GET: Files/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var files = _db.Include(f => f.Group).Include(f => f.OwnerNavigation).FirstOrDefaultAsync(m => m.Id == id);
            if (files == null)
            {
                return NotFound();
            }

            return View(files);
        }

        // POST: Files/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            _db.Delete(id);
            _db.Save();
            return RedirectToAction(nameof(Index));
        }

        private bool FilesExists(int id)
        {
            return _db.Exists(id);
        }
    }
}
