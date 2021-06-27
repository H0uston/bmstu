from jsonschema import exceptions, validate
import json
import os


def main(schema: str, doc: str):
    f_schema = open(schema)
    f_doc = open(doc)
    if f_schema and f_doc:
        schema = json.load(f_schema)
        f_schema.close()

        for line in f_doc:
            with open("buffer.txt", "w") as f:
                f.write(line)
            with open("buffer.txt", "r") as f:
                line = json.load(f)
            try:
                validate(instance=line, schema=schema)
            except exceptions.ValidationError:
                print(line)
                print("Is not valid")
        f_doc.close()

    os.remove(os.getcwd() + "/buffer.txt")
    print("Is valid")


if __name__ == "__main__":
    SCHEMA = "/Users/houston/Documents/GitHub/Databases/Cargo_transportation/lab_5/customers.json"
    DOC = "/Users/houston/Documents/GitHub/Databases/Cargo_transportation/lab_5/customers.txt"
    main(SCHEMA, DOC)