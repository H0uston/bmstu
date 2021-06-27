

\COPY (SELECT table_to_xml('suppliers', true, true, '')) to '/Users/houston/documents/github/database/lab_6/suppliers_data.xml';

