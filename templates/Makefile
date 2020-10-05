CONFIGS_DIR = $(ASSETS_DIRECTORY)/configs
FONTS_DIR = $(ASSETS_DIRECTORY)/fonts
ASSETS_LIST = $(CONFIGS_DIR)/game.yaml

generate: assets-dir $(ASSETS_LIST)
	@echo "Generating assets from templates"

assets-dir:
	@mkdir -p $(ASSETS_DIRECTORY)
	@mkdir -p $(CONFIGS_DIR)
	@mkdir -p $(FONTS_DIR)

$(CONFIGS_DIR)/game.yaml: $(TEMPLATES_DIRECTORY)/game.yaml
	@cp $< $@
