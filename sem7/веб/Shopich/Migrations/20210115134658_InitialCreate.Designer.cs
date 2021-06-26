﻿// <auto-generated />
using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using Npgsql.EntityFrameworkCore.PostgreSQL.Metadata;
using Shopich.Models;

namespace Shopich.Migrations
{
    [DbContext(typeof(ShopichContext))]
    [Migration("20210115134658_InitialCreate")]
    partial class InitialCreate
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .UseIdentityByDefaultColumns()
                .HasAnnotation("Relational:Collation", "Russian_Russia.1251")
                .HasAnnotation("Relational:MaxIdentifierLength", 63)
                .HasAnnotation("ProductVersion", "5.0.1");

            modelBuilder.Entity("Shopich.Models.Categories", b =>
                {
                    b.Property<int>("CategoriesId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("integer")
                        .HasColumnName("categories_id")
                        .UseIdentityByDefaultColumn();

                    b.Property<int>("CategoryId")
                        .HasColumnType("integer")
                        .HasColumnName("category_id");

                    b.Property<int>("ProductId")
                        .HasColumnType("integer")
                        .HasColumnName("product_id");

                    b.HasKey("CategoriesId")
                        .HasName("categories_pkey");

                    b.HasIndex("CategoryId");

                    b.HasIndex("ProductId");

                    b.ToTable("categories");
                });

            modelBuilder.Entity("Shopich.Models.Category", b =>
                {
                    b.Property<int>("CategoryId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("integer")
                        .HasColumnName("category_id")
                        .UseIdentityByDefaultColumn();

                    b.Property<string>("CategoryDescription")
                        .HasColumnType("text")
                        .HasColumnName("category_description");

                    b.Property<string>("CategoryName")
                        .IsRequired()
                        .HasColumnType("text")
                        .HasColumnName("category_name");

                    b.HasKey("CategoryId");

                    b.ToTable("category");
                });

            modelBuilder.Entity("Shopich.Models.Order", b =>
                {
                    b.Property<int>("OrderId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("integer")
                        .HasColumnName("order_id")
                        .UseIdentityByDefaultColumn();

                    b.Property<bool>("IsApproved")
                        .HasColumnType("boolean")
                        .HasColumnName("is_approved");

                    b.Property<DateTime?>("OrderDate")
                        .HasColumnType("date")
                        .HasColumnName("order_date");

                    b.Property<int>("UserId")
                        .HasColumnType("integer")
                        .HasColumnName("user_id");

                    b.HasKey("OrderId")
                        .HasName("order_pkey");

                    b.HasIndex("UserId");

                    b.ToTable("order");
                });

            modelBuilder.Entity("Shopich.Models.Orders", b =>
                {
                    b.Property<int>("OrdersId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("integer")
                        .HasColumnName("orders_id")
                        .UseIdentityByDefaultColumn();

                    b.Property<int>("Count")
                        .HasColumnType("integer")
                        .HasColumnName("count");

                    b.Property<int>("OrderId")
                        .HasColumnType("integer")
                        .HasColumnName("order_id");

                    b.Property<int>("ProductId")
                        .HasColumnType("integer")
                        .HasColumnName("product_id");

                    b.HasKey("OrdersId")
                        .HasName("orders_pkey");

                    b.HasIndex("OrderId");

                    b.HasIndex("ProductId");

                    b.ToTable("orders");
                });

            modelBuilder.Entity("Shopich.Models.Product", b =>
                {
                    b.Property<int>("ProductId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("integer")
                        .HasColumnName("product_id")
                        .UseIdentityByDefaultColumn();

                    b.Property<bool>("ProductAvailability")
                        .HasColumnType("boolean")
                        .HasColumnName("product_availability");

                    b.Property<int?>("ProductDiscount")
                        .HasColumnType("integer")
                        .HasColumnName("product_discount");

                    b.Property<string>("ProductName")
                        .IsRequired()
                        .HasColumnType("text")
                        .HasColumnName("product_name");

                    b.Property<string>("ProductPhotoPath")
                        .HasColumnType("text");

                    b.Property<double>("ProductPrice")
                        .HasColumnType("double precision")
                        .HasColumnName("product_price");

                    b.HasKey("ProductId");

                    b.ToTable("product");
                });

            modelBuilder.Entity("Shopich.Models.Review", b =>
                {
                    b.Property<int>("ReviewId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("integer")
                        .HasColumnName("review_id")
                        .UseIdentityByDefaultColumn();

                    b.Property<int>("ProductId")
                        .HasColumnType("integer")
                        .HasColumnName("product_id");

                    b.Property<DateTime>("ReviewDate")
                        .HasColumnType("date")
                        .HasColumnName("review_date");

                    b.Property<int>("ReviewRating")
                        .HasColumnType("integer")
                        .HasColumnName("review_rating");

                    b.Property<string>("ReviewText")
                        .IsRequired()
                        .HasColumnType("text")
                        .HasColumnName("review_text");

                    b.Property<int>("UserId")
                        .HasColumnType("integer")
                        .HasColumnName("user_id");

                    b.HasKey("ReviewId");

                    b.HasIndex("ProductId");

                    b.HasIndex("UserId");

                    b.ToTable("review");
                });

            modelBuilder.Entity("Shopich.Models.Role", b =>
                {
                    b.Property<int>("RoleId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("integer")
                        .HasColumnName("role_id")
                        .UseIdentityByDefaultColumn();

                    b.Property<string>("RoleDescription")
                        .HasColumnType("text")
                        .HasColumnName("role_description");

                    b.Property<string>("RoleName")
                        .IsRequired()
                        .HasColumnType("text")
                        .HasColumnName("role_name");

                    b.HasKey("RoleId");

                    b.ToTable("role");
                });

            modelBuilder.Entity("Shopich.Models.User", b =>
                {
                    b.Property<int>("UserId")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("integer")
                        .HasColumnName("user_id")
                        .UseIdentityByDefaultColumn();

                    b.Property<int>("RoleId")
                        .HasColumnType("integer")
                        .HasColumnName("role_id");

                    b.Property<DateTime?>("UserBirthday")
                        .HasColumnType("date")
                        .HasColumnName("user_birthday");

                    b.Property<string>("UserCity")
                        .HasColumnType("text")
                        .HasColumnName("user_city");

                    b.Property<string>("UserEmail")
                        .IsRequired()
                        .HasColumnType("text")
                        .HasColumnName("user_email");

                    b.Property<string>("UserFlat")
                        .HasColumnType("text")
                        .HasColumnName("user_flat");

                    b.Property<string>("UserHouse")
                        .HasColumnType("text")
                        .HasColumnName("user_house");

                    b.Property<int?>("UserIndex")
                        .HasColumnType("integer")
                        .HasColumnName("user_index");

                    b.Property<string>("UserName")
                        .HasColumnType("text")
                        .HasColumnName("user_name");

                    b.Property<string>("UserPassword")
                        .IsRequired()
                        .HasColumnType("text")
                        .HasColumnName("user_password");

                    b.Property<string>("UserPhone")
                        .HasColumnType("text")
                        .HasColumnName("user_phone");

                    b.Property<string>("UserStreet")
                        .HasColumnType("text")
                        .HasColumnName("user_street");

                    b.Property<string>("UserSurname")
                        .HasColumnType("text")
                        .HasColumnName("user_surname");

                    b.HasKey("UserId");

                    b.HasIndex("RoleId");

                    b.ToTable("user");
                });

            modelBuilder.Entity("Shopich.Models.Categories", b =>
                {
                    b.HasOne("Shopich.Models.Category", "Category")
                        .WithMany("CategoryCollection")
                        .HasForeignKey("CategoryId")
                        .HasConstraintName("categories_category_id_fkey")
                        .IsRequired();

                    b.HasOne("Shopich.Models.Product", "Product")
                        .WithMany("CategoryCollection")
                        .HasForeignKey("ProductId")
                        .HasConstraintName("categories_product_id_fkey")
                        .IsRequired();

                    b.Navigation("Category");

                    b.Navigation("Product");
                });

            modelBuilder.Entity("Shopich.Models.Order", b =>
                {
                    b.HasOne("Shopich.Models.User", "User")
                        .WithMany("OrderCollection")
                        .HasForeignKey("UserId")
                        .HasConstraintName("order_user_id_fkey")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("User");
                });

            modelBuilder.Entity("Shopich.Models.Orders", b =>
                {
                    b.HasOne("Shopich.Models.Order", "OrderNavigation")
                        .WithMany("OrderCollection")
                        .HasForeignKey("OrderId")
                        .HasConstraintName("orders_order_id_fkey")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("Shopich.Models.Product", "Product")
                        .WithMany("Orders")
                        .HasForeignKey("ProductId")
                        .HasConstraintName("orders_product_id_fkey")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("OrderNavigation");

                    b.Navigation("Product");
                });

            modelBuilder.Entity("Shopich.Models.Review", b =>
                {
                    b.HasOne("Shopich.Models.Product", "Product")
                        .WithMany("Reviews")
                        .HasForeignKey("ProductId")
                        .HasConstraintName("review_product_id_fkey")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.HasOne("Shopich.Models.User", "User")
                        .WithMany("Reviews")
                        .HasForeignKey("UserId")
                        .HasConstraintName("review_user_id_fkey")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Product");

                    b.Navigation("User");
                });

            modelBuilder.Entity("Shopich.Models.User", b =>
                {
                    b.HasOne("Shopich.Models.Role", "Role")
                        .WithMany("Users")
                        .HasForeignKey("RoleId")
                        .HasConstraintName("user_role_id_fkey")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Role");
                });

            modelBuilder.Entity("Shopich.Models.Category", b =>
                {
                    b.Navigation("CategoryCollection");
                });

            modelBuilder.Entity("Shopich.Models.Order", b =>
                {
                    b.Navigation("OrderCollection");
                });

            modelBuilder.Entity("Shopich.Models.Product", b =>
                {
                    b.Navigation("CategoryCollection");

                    b.Navigation("Orders");

                    b.Navigation("Reviews");
                });

            modelBuilder.Entity("Shopich.Models.Role", b =>
                {
                    b.Navigation("Users");
                });

            modelBuilder.Entity("Shopich.Models.User", b =>
                {
                    b.Navigation("OrderCollection");

                    b.Navigation("Reviews");
                });
#pragma warning restore 612, 618
        }
    }
}
