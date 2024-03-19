#!/bin/sh

DEST_FILE_NAME="rendu.pdf"
TEMPLATE="eisvogel.tex"
DATE=$(date "+%d %B %Y")
DATA_DIR="pandoc"

SOURCE_FORMAT="markdown_strict\
+backtick_code_blocks\
+pipe_tables\
+auto_identifiers\
+yaml_metadata_block\
+implicit_figures\
+table_captions\
+footnotes\
+smart\
+escaped_line_breaks\
+header_attributes"

pandoc -s -o "$DEST_FILE_NAME" -f "$SOURCE_FORMAT" --data-dir="$DATA_DIR" --template "$TEMPLATE" --toc --listings --columns=50 --number-sections --dpi=300 --pdf-engine xelatex -M date="$DATE" md/HEADER.YAML md/*.md >&1


