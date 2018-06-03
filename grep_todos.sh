#!/bin/bash
grep -REi 'TODO|FixMe' . | grep -vE 'Binary|grep_todos.sh'
