import os
Import("env")

# Pfad zum Python-Projekt relativ zum PIO-Projektordner
# "../mein-python-toolset" springt einen Ordner hoch und in das Zielverzeichnis
python_project_dir = os.path.abspath(os.path.join(env.get("PROJECT_DIR"), "..", "synthhead-buildutils"))
pyproject_toml = os.path.join(python_project_dir, "pyproject.toml")

if os.path.exists(pyproject_toml):
    print(f"--- Installiere Python-Projekt von: {python_project_dir} ---")
    
    # Installiert das externe Projekt im 'Editable Mode' (-e)
    # Damit werden alle 'dependencies' aus dessen pyproject.toml in PIO geladen
    env.Execute(f'$PYTHONEXE -m pip install -e "{python_project_dir}"')
else:
    print(f"Fehler: pyproject.toml nicht gefunden unter {pyproject_toml}")


# Custom Target hinzufügen
from synthhead import release

env.AddTarget(
    name="release_create",
    dependencies=[],
    actions=[
        release.create,                    # Python-Funktion aufrufen
    ],
    group="SynthHead",
    title="Create Release",
    description="Erzeugt ein neues Release."
)
