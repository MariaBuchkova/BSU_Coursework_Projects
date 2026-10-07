SRC_DIR  = src
OUT_DIR  = out
JAR      = schedule.jar
MAIN     = class_scedule_lab4.main
SOURCES  = $(shell find $(SRC_DIR) -name "*.java")

.PHONY: clean build run

clean:
	rm -rf $(OUT_DIR) $(JAR)

build: clean
	mkdir -p $(OUT_DIR)
	javac -encoding UTF-8 -d $(OUT_DIR) $(SOURCES)
	jar cfe $(JAR) $(MAIN) -C $(OUT_DIR) .

run:
	java -ea -jar $(JAR)