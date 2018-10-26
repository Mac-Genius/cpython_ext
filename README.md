# Python Generic C Extension

## Reproducing the crash:

1. Ensure you are using the latest 3.6.X or 3.7.X version with debug
2. Clone the repo
3. Create virtualenv: `virtualenv -p $(which python3.6) .env`
4. source .env: `source .env/bin/activate`
5. build extension: `python setup.py build`
6. Install the extension: `pip install .`
7. Run python interpreter: `python`
8. enter the following into the interpreter:

```python
from cpython import CPython
with CPython() as f:
    print(f.field1)

exit()
```

You should see `Segmentation fault` when it exits.
