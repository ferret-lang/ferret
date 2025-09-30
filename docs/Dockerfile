# Stage 1: Build the Next.js application
FROM node:22-alpine AS builder

WORKDIR /app

# Copy package.json and package-lock.json 
COPY package.json package-lock.json source.config.ts ./

# Install dependencies
RUN npm ci --verbose 
RUN npm install --save-dev vite

# Copy the rest of the application code
COPY . .

# Build the Next.js application
RUN npm run build

# Stage 2: Serve the Next.js application
FROM node:22-alpine AS runner

WORKDIR /app

# Copy necessary files from the builder stage
COPY --from=builder /app/.next ./.next
COPY --from=builder /app/node_modules ./node_modules
COPY --from=builder /app/package.json ./package.json

# Set environment variables (if needed)
ENV NODE_ENV=production
ENV PORT=3000

# Expose the port Next.js will run on
EXPOSE 3000

# Command to start the Next.js application
CMD ["npm", "start"]
