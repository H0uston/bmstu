CREATE DATABASE Transportation OWNER houston;

CREATE TABLE Customers
(
    id_customer integer NOT NULL,
    name_customer text NOT NULL,
    city_customer text NOT NULL,
    index_customer integer NOT NULL,
    CHECK(id_customer > 0),
    CHECK(index_customer > 0),
    PRIMARY KEY (id_customer)
);

\copy Customers from '/Users/houston/Documents/GitHub/Databases/Cargo_transportation/new_data/customers_data.csv' WITH (FORMAT csv);

CREATE TABLE Suppliers
(
    id_supplier integer NOT NULL,
    name_supplier text NOT NULL,
    city_supplier text NOT NULL,
    sector_supplier text NOT NULL,
    CHECK(id_supplier > 0),
    PRIMARY KEY (id_supplier)
);

ALTER TABLE suppliers ADD COLUMN owner integer;

\copy Suppliers from '/Users/houston/Documents/GitHub/Databases/Cargo_transportation/data/suppliers_data.csv' WITH (FORMAT csv);

CREATE TABLE Trip
(
    id_trip integer NOT NULL,
    from_trip text NOT NULL,
    to_trip text NOT NULL,
    start_date_trip date NOT NULL,
    end_data_trip date NOT NULL,
    PRIMARY KEY (id_trip)
);

\copy Trip from '/Users/houston/Documents/GitHub/Databases/Cargo_transportation/data/trip_data.csv' WITH (FORMAT csv);

CREATE TABLE Cargo
(
    weight_cargo float4 NOT NULL,
    id_customer integer NOT NULL REFERENCES Customers (id_customer),
    id_supplier integer NOT NULL REFERENCES Suppliers (id_supplier),
    id_trip integer NOT NULL REFERENCES Trip (id_trip),
    PRIMARY KEY (id_customer, id_supplier, id_trip)
);

\copy Cargo from '/Users/houston/Documents/GitHub/Databases/Cargo_transportation/data/cargo_data.csv' WITH (FORMAT csv);

