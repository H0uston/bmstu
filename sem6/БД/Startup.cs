using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.HttpsPolicy;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.EntityFrameworkCore;
using DistanceLearning.Models;
using Microsoft.AspNetCore.Authentication.Cookies;
using DistanceLearning.Repositories.interfaces;
using DistanceLearning.Repositories.implementations;

namespace DistanceLearning
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        // This method gets called by the runtime. Use this method to add services to the container.
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddDbContext<DistanceLearningDBContext>(option =>
                option.UseNpgsql(Configuration.GetConnectionString("DistanceLearningDB")));

            // установка конфигурации подключени€
            services.AddAuthentication(CookieAuthenticationDefaults.AuthenticationScheme)
                .AddCookie(options =>
                {
                    // ѕуть аутентификации, по которому будет перенаправлен не залогиненый пользователь
                    options.LoginPath = new Microsoft.AspNetCore.Http.PathString("/Account/Login");
                });


            services.AddControllersWithViews();
            scopeInterfaceRepository(services);
        }

        public void scopeInterfaceRepository(IServiceCollection services)
        {
            services.AddScoped<ICategory, PostgreSQLCategoryRepository>();
            services.AddScoped<IFile, PostgreSQLFilesRepository>();
            services.AddScoped<IGroupDescription, PostgreSQLGroupDescriptionRepository>();
            services.AddScoped<IParticipation, PostgreSQLParticipationRepository>();
            services.AddScoped<IProgress, PostgreSQLProgressRepository>();
            services.AddScoped<IRequestList, PostgreSQLRequestListRepository>();
            services.AddScoped<IRole, PostgreSQLRoleRepository>();
            services.AddScoped<IUniversity, PostgreSQLUniversityRepository>();
            services.AddScoped<IUserDescription, PostgreSQLUserDescriptionRepository>();
        }

        private void UpdateDatabase(IApplicationBuilder app)
        {
            using (var serviceScope = app.ApplicationServices.GetRequiredService<IServiceScopeFactory>().CreateScope())
            {
                using (var context = serviceScope.ServiceProvider.GetService<DistanceLearningDBContext>())
                {
                    context.Database.Migrate();
                }
            }
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            UpdateDatabase(app);
            if (env.IsDevelopment())
            {
                app.UseDeveloperExceptionPage();
            }
            else
            {
                app.UseExceptionHandler("/Home/Error");
                // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
                app.UseHsts();
            }
            app.UseHttpsRedirection();
            app.UseStaticFiles();

            app.UseRouting();

            app.UseAuthentication();  // кто пользователь
            app.UseAuthorization();  // какие права в системе имеет пользователь

            app.UseEndpoints(endpoints =>
            {
                endpoints.MapControllerRoute(
                    name: "default",
                    pattern: "{controller=Home}/{action=Index}/{id?}");
            });
        }
    }
}
