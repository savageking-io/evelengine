ASSETS_PATH=../assets
ASSETS_LIST=$(ASSETS_PATH)/fonts \
			$(ASSETS_PATH)/configs \
			$(ASSETS_PATH)/configs/game.yaml

generate: $(ASSETS_LIST)

$(ASSETS_PATH)/fonts:
	@mkdir -p $@

$(ASSETS_PATH)/configs:
	@mkdir -p $@

$(ASSETS_PATH)/configs/game.yaml: game.yaml
	@cp $< $@
