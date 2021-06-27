using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;

namespace DistanceLearning
{
    public partial class DistanceLearningDBContext : DbContext
    {
        public DistanceLearningDBContext()
        {
        }

        public DistanceLearningDBContext(DbContextOptions<DistanceLearningDBContext> options)
            : base(options)
        {
        }

        public virtual DbSet<Category> Category { get; set; }
        public virtual DbSet<Files> Files { get; set; }
        public virtual DbSet<GroupDescription> GroupDescription { get; set; }
        public virtual DbSet<Participation> Participation { get; set; }
        public virtual DbSet<Progress> Progress { get; set; }
        public virtual DbSet<RequestList> RequestList { get; set; }
        public virtual DbSet<Role> Role { get; set; }
        public virtual DbSet<University> University { get; set; }
        public virtual DbSet<UserDescription> UserDescription { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
                optionsBuilder.UseNpgsql("Server=localhost;Port=5432;Database=DistanceLearningDB;Username=postgres;password=postgres");
            }
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<Category>(entity =>
            {
                entity.ToTable("category");

                entity.Property(e => e.Id)
                    .HasColumnName("id")
                    .ValueGeneratedNever();

                entity.Property(e => e.Description).HasColumnName("description");

                entity.Property(e => e.Name)
                    .IsRequired()
                    .HasColumnName("name");
            });

            modelBuilder.Entity<Files>(entity =>
            {
                entity.ToTable("files");

                entity.Property(e => e.Id)
                    .HasColumnName("id")
                    .ValueGeneratedOnAdd();

                entity.Property(e => e.DateOfLoad)
                    .HasColumnName("date_of_load")
                    .HasColumnType("date");

                entity.Property(e => e.GroupId).HasColumnName("group_id");

                entity.Property(e => e.Name)
                    .IsRequired()
                    .HasColumnName("name");

                entity.Property(e => e.Owner).HasColumnName("owner");

                entity.Property(e => e.Path)
                    .IsRequired()
                    .HasColumnName("path");

                entity.HasOne(d => d.Group)
                    .WithMany(p => p.Files)
                    .HasForeignKey(d => d.GroupId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("files_group_id_fkey");

                entity.HasOne(d => d.OwnerNavigation)
                    .WithMany(p => p.Files)
                    .HasForeignKey(d => d.Owner)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("files_owner_fkey");
            });

            modelBuilder.Entity<GroupDescription>(entity =>
            {
                entity.ToTable("group_description");

                entity.Property(e => e.Id)
                    .HasColumnName("id")
                    .ValueGeneratedOnAdd();

                entity.Property(e => e.GroupCategory).HasColumnName("group_category");

                entity.Property(e => e.IconPath).HasColumnName("icon_path");

                entity.Property(e => e.Name)
                    .IsRequired()
                    .HasColumnName("name");

                entity.Property(e => e.Private).HasColumnName("private");

                entity.HasOne(d => d.GroupCategoryNavigation)
                    .WithMany(p => p.GroupDescription)
                    .HasForeignKey(d => d.GroupCategory)
                    .HasConstraintName("group_description_group_category_fkey");
            });

            modelBuilder.Entity<Participation>(entity =>
            {
                entity.HasKey(e => new { e.UserId, e.GroupId })
                    .HasName("participation_pkey");

                entity.ToTable("participation");

                entity.Property(e => e.UserId).HasColumnName("user_id");

                entity.Property(e => e.GroupId).HasColumnName("group_id");

                entity.Property(e => e.ProgressId).HasColumnName("progress_id");

                entity.Property(e => e.Role).HasColumnName("role");

                entity.HasOne(d => d.Group)
                    .WithMany(p => p.Participation)
                    .HasForeignKey(d => d.GroupId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("participation_group_id_fkey");

                entity.HasOne(d => d.Progress)
                    .WithMany(p => p.Participation)
                    .HasForeignKey(d => d.ProgressId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("participation_progress_id_fkey");

                entity.HasOne(d => d.RoleNavigation)
                    .WithMany(p => p.Participation)
                    .HasForeignKey(d => d.Role)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("participation_role_fkey");

                entity.HasOne(d => d.User)
                    .WithMany(p => p.Participation)
                    .HasForeignKey(d => d.UserId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("participation_user_id_fkey");
            });

            modelBuilder.Entity<Progress>(entity =>
            {
                entity.ToTable("progress");

                entity.Property(e => e.Id)
                    .HasColumnName("id")
                    .ValueGeneratedNever();

                entity.Property(e => e.CompletedTasks).HasColumnName("completed_tasks");

                entity.Property(e => e.TotalCountTasks).HasColumnName("total_count_tasks");
            });

            modelBuilder.Entity<RequestList>(entity =>
            {
                entity.HasKey(e => new { e.UserId, e.GroupId })
                    .HasName("request_list_pkey");

                entity.ToTable("request_list");

                entity.Property(e => e.UserId).HasColumnName("user_id");

                entity.Property(e => e.GroupId).HasColumnName("group_id");

                entity.Property(e => e.IsAccepted).HasColumnName("is_accepted");

                entity.Property(e => e.IsAwaiting).HasColumnName("is_awaiting");

                entity.Property(e => e.IsDenied).HasColumnName("is_denied");

                entity.HasOne(d => d.Group)
                    .WithMany(p => p.RequestList)
                    .HasForeignKey(d => d.GroupId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("request_list_group_id_fkey");

                entity.HasOne(d => d.User)
                    .WithMany(p => p.RequestList)
                    .HasForeignKey(d => d.UserId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("request_list_user_id_fkey");
            });

            modelBuilder.Entity<Role>(entity =>
            {
                entity.ToTable("role");

                entity.Property(e => e.Id)
                    .HasColumnName("id")
                    .ValueGeneratedNever();

                entity.Property(e => e.Description)
                    .HasColumnName("description");

                entity.Property(e => e.Name)
                    .IsRequired()
                    .HasColumnName("name");
            });

            modelBuilder.Entity<University>(entity =>
            {
                entity.ToTable("university");

                entity.Property(e => e.Id)
                    .HasColumnName("id")
                    .ValueGeneratedNever();

                entity.Property(e => e.Name)
                    .IsRequired()
                    .HasColumnName("name");
            });

            modelBuilder.Entity<UserDescription>(entity =>
            {
                entity.ToTable("user_description");

                entity.Property(e => e.Id)
                    .HasColumnName("id")
                    .ValueGeneratedOnAdd();

                entity.Property(e => e.Birthday)
                    .HasColumnName("birthday")
                    .HasColumnType("date");

                entity.Property(e => e.Email)
                    .IsRequired()
                    .HasColumnName("email");

                entity.Property(e => e.Name)
                    .IsRequired()
                    .HasColumnName("name");

                entity.Property(e => e.Password)
                    .IsRequired()
                    .HasColumnName("password");

                entity.Property(e => e.University).HasColumnName("university");

                entity.Property(e => e.Role)
                    .IsRequired()
                    .HasColumnName("role");

                entity.HasOne(d => d.UniversityNavigation)
                    .WithMany(p => p.UserDescription)
                    .HasForeignKey(d => d.University)
                    .HasConstraintName("user_description_university_fkey");
            });

            OnModelCreatingPartial(modelBuilder);
        }

        partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
    }
}
