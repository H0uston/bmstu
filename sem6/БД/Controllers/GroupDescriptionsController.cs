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
    public class GroupDescriptionsController : Controller
    {
        private readonly IGroupDescription _db;

        public GroupDescriptionsController(IGroupDescription context)
        {
            _db = context;
        }

        [Authorize(Roles = "Admin")]
        // GET: GroupDescriptions
        public async Task<IActionResult> Index()
        {
            var distanceLearningDBContext = _db.Include(g => g.GroupCategoryNavigation);
            return View(await distanceLearningDBContext.ToListAsync());
        }

        // GET: GroupDescriptions/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var groupDescription = _db.Include(g => g.GroupCategoryNavigation).FirstOrDefaultAsync(m => m.Id == id);
            if (groupDescription == null)
            {
                return NotFound();
            }

            return View(groupDescription);
        }

        // GET: GroupDescriptions/Create
        public IActionResult Create()
        {
            ViewData["GroupCategory"] = new SelectList(_db.GetCategories(), "Id", "Name");
            return View();
        }

        // POST: GroupDescriptions/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,Name,Private,GroupCategory,IconPath")] GroupDescription groupDescription)
        {
            if (ModelState.IsValid)
            {
                _db.Create(groupDescription);
                _db.Save();
                return RedirectToAction(nameof(Index));
            }
            ViewData["GroupCategory"] = new SelectList(_db.GetCategories(), "Id", "Name", groupDescription.GroupCategory);
            return View(groupDescription);
        }

        // GET: GroupDescriptions/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var groupDescription = _db.GetElement(id.GetValueOrDefault());
            if (groupDescription == null)
            {
                return NotFound();
            }
            ViewData["GroupCategory"] = new SelectList(_db.GetCategories(), "Id", "Name", groupDescription.GroupCategory);
            return View(groupDescription);
        }

        // POST: GroupDescriptions/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,Name,Private,GroupCategory,IconPath")] GroupDescription groupDescription)
        {
            if (id != groupDescription.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _db.Update(groupDescription);
                    _db.Save();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!GroupDescriptionExists(groupDescription.Id))
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
            ViewData["GroupCategory"] = new SelectList(_db.GetCategories(), "Id", "Name", groupDescription.GroupCategory);
            return View(groupDescription);
        }

        // GET: GroupDescriptions/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var groupDescription = _db.Include(g => g.GroupCategoryNavigation).FirstOrDefaultAsync(m => m.Id == id);
            if (groupDescription == null)
            {
                return NotFound();
            }

            return View(groupDescription);
        }

        // POST: GroupDescriptions/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            _db.Delete(id);
            _db.Save();
            return RedirectToAction(nameof(Index));
        }

        private bool GroupDescriptionExists(int id)
        {
            return _db.Exists(id);
        }
    }
}
