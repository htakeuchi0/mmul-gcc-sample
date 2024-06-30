#!/bin/bash

pushd script >/dev/null

if ! [ -e .venv ]; then
  python3 -m venv .venv
  .venv/bin/python -m pip install -r requirements.txt
fi

.venv/bin/python plot.py

popd >/dev/null
