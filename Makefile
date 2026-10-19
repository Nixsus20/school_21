.PHONY: help check check-local

help:
	@echo "make check        - full C + SQL smoke checks using Docker"
	@echo "make check-local  - compile and test C locally (SQL skipped)"

check:
	@command -v docker >/dev/null 2>&1 || { \
		echo "Docker is required for the full check. Install Docker or run 'make check-local'."; \
		exit 2; \
	}
	@docker build -t school21-verify .
	@docker run --rm school21-verify

check-local:
	@bash scripts/check.sh
